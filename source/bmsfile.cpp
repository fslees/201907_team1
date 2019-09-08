//=============================================================================
//
// 譜面データ処理 [bmsfile.cpp]
// Author : GP12A332_26_田中太陽
//
//=============================================================================
#pragma warning( disable : 4996 )
#include "bmsfile.h"
#include <stdio.h>

#define DEBUGMODE

#define SAFE_FREE(x)		{ if(x) { free(x); x=NULL; } }

////////////////////////////////////////////
// コンストラクタ
////////////////////////////////////////////
BmsFile::BmsFile( void )
{
	ZeroMemory( &mBH,sizeof(mBH) );
	ZeroMemory( &pBmsData,sizeof(pBmsData) );
	ZeroMemory( &iBmsData,sizeof(iBmsData) );
	ZeroMemory( &mWavFile,sizeof(mWavFile) );
	ZeroMemory( &mBmpFile,sizeof(mBmpFile) );
	ZeroMemory( &mBmsBar,sizeof(mBmsBar) );
	ZeroMemory( &mLastError,sizeof(mLastError) );

	// デフォルト値セット
	Clear();
}

////////////////////////////////////////////
// デストラクタ
////////////////////////////////////////////
BmsFile::~BmsFile()
{
	Clear();
}

////////////////////////////////////////////
// データの初期化
////////////////////////////////////////////
BOOL BmsFile::Clear( void )
{
	int i;

	// ヘッダ初期化
	ZeroMemory( &mBH,sizeof(mBH) );
	mBH.lPlayer	= 1;
	mBH.fBpm	= 130;
	for( i=0;i<BMS_MAXBUFFER;i++ ) {
		mBH.fBpmIndex[i] = 120.0f;
	}

	// 実データ初期化
	for( i=0;i<BMS_MAXBUFFER;i++ ) {
		SAFE_FREE( pBmsData[i] );		// BMSデータ領域をクリア
		iBmsData[i] = 0;				// データの数をクリア
	}

	// ファイル名
	ZeroMemory( &mWavFile,sizeof(mWavFile) );
	ZeroMemory( &mBmpFile,sizeof(mBmpFile) );

	// 小節の長さを1.0で初期化
	ZeroMemory( &mBmsBar,sizeof(mBmsBar) );
	for( int i=0;i<1001;i++ ) {
		mBmsBar[i].fScale = 1.0f;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////
// ヘッダ情報だけを取り出す
////////////////////////////////////////////////////////////////////////////////////////
BOOL BmsFile::LoadHeader( const char *file )
{
	Clear();

	FILE *fp;
	fp = fopen( file,"r" );
	if( !fp ) {
		sprintf( mLastError,"[%s] ファイルが見つからない",file );
		return FALSE;
	}

	char buf[1024];
	char tmp[4];
	int num;
	int ch;
	int line;

	while(1) {
		// 1行を読みこむ
		ZeroMemory( buf,1024 );
		fgets( buf,1024,fp );
		if( buf[0]==NULL && feof(fp) )	// ファイルの終端なら検索終わり
			break;

		// コマンド以外なら飛ばす
		if( buf[0]!='#' )
			continue;

		// 最後の改行を消去
		if( buf[strlen(buf)-1]=='\n' )
			buf[strlen(buf)-1] = NULL;

		// コマンドの解析
		int cmd = GetCommand( buf );

		// 不明なコマンドならスキップ
		if( cmd<=-2 ) {
			continue;
		}

		// パラメータの分割
		char str[1024];
		ZeroMemory( str,1024 );
		if( !GetCommandString(buf,str) ) {
			// 文字列の取得が失敗なら
			fclose(fp);
			sprintf( mLastError,"[%s] パラメータの分割エラー",buf );
			return FALSE;
		}

		// パラメータの代入
		switch( cmd )
		{
		case 0:		// PLAYER
			mBH.lPlayer = atoi( str );
			break;
		case 1:		// GENRE
			strcpy( mBH.mGenre,str );
			break;
		case 2:		// TITLE
			strcpy( mBH.mTitle,str );
			break;
		case 3:		// ARTIST
			strcpy( mBH.mArtist,str );
			break;
		case 4:		// BPM
			if( buf[4]==' ' || buf[4]==0x09 ) {
				// 基本コマンドなら
				mBH.fBpm = (float)atof( str );
				AddData( BMS_TEMPO,0,(LONG)mBH.fBpm );
			} else {
				// 拡張コマンドなら
				ZeroMemory( tmp,sizeof(tmp) );
				tmp[0] = buf[4];
				tmp[1] = buf[5];
				tmp[2] = NULL;
				ch = atoi1610( tmp );	// 16進数
				mBH.fBpmIndex[ch] = (float)atof( str );
			}
			break;
		case 5:		// MIDIFILE
			strcpy( mBH.mMidifile,str );
			break;
		case 6:		// PLAYLEVEL
			mBH.lPlaylevel = atoi( str );
			break;
		case 7:		// RANK
			mBH.lRank	= atoi( str );
			break;
		case 8:		// VOLWAV
			mBH.lWavVol	= atoi( str );
			break;
		case 9:		// TOTAL
			mBH.lTotal	= atoi( str );
			break;
		case 10:	// StageFile
			strcpy( mBH.mStagePic,str );
			break;
		case 11:	// WAV
			ZeroMemory( tmp,sizeof(tmp) );
			tmp[0] = buf[4];
			tmp[1] = buf[5];
			num = atoi1610( tmp );			// 16進数
			strcpy( mWavFile[num],str );
			break;
		case 12:	// BMP
			ZeroMemory( tmp,sizeof(tmp) );
			tmp[0] = buf[4];
			tmp[1] = buf[5];
			num = atoi1610( tmp );			// 16進数
			strcpy( mBmpFile[num],str );
			break;
		default:
			// 小節番号の取得
			ZeroMemory( tmp,sizeof(tmp) );
			memcpy( tmp,buf+1,3 );
			line = atoi( tmp );			// 10進数
			// チャンネル番号の取得
			ZeroMemory( tmp,sizeof(tmp) );
			tmp[0] = buf[4];
			tmp[1] = buf[5];
			ch = atoi1610( tmp );		// 16進数
			if( ch==BMS_STRETCH ) {
				// 小節の倍率変更命令の場合
				mBmsBar[line].fScale = (float)atof( str );
			}
			// 小節番号の最大値を記憶する
			if( mBH.lEndBar < line )
				mBH.lEndBar = line;
			break;
		}
	}

	// 最後の小節内にもデータが存在するため、その次の小節を終端小節とする
	mBH.lEndBar++;

	// 小節倍率データを元に全ての小節情報を算出
	LONG cnt = 0;	// 現在の小節の開始カウント値
	int i;
	for( i=0;i<=mBH.lEndBar;i++ ) {
		// 小節リストを加算
		mBmsBar[i].lTime	= cnt;												// 現在の小節の開始カウントを記録
		mBmsBar[i].lLength	= (LONG)(BMS_RESOLUTION * mBmsBar[i].fScale);		// 倍率からこの小節の長さカウント値を算出
		
		// この小節のカウント数を加算して次の小節の開始カウントとする
		cnt += mBmsBar[i].lLength;
	}

	// 最大カウントを保存
	mBH.lMaxCount = cnt;

	fclose( fp );

	return TRUE;
}

////////////////////////////////////////////
// データロード
////////////////////////////////////////////
BOOL BmsFile::Load( const char *file )
{
	// ヘッダ＆小節倍率の読み込み
	if( !LoadHeader(file) ) {
		return FALSE;
	}

	// 実データの読み込み
	if( !LoadBmsData(file) ) {
		return FALSE;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////
// BMSファイルにセーブ
////////////////////////////////////////////////////////////////////////////////////////
BOOL BmsFile::Save( const char *file )
{
	FILE *fp;
	fp = fopen( file,"wb" );
	if( !fp ) {
		sprintf( mLastError,"[%s] ファイル書き込みエラー",file );
		return FALSE;
	}

	// ヘッダの書き出し
	fprintf( fp,"; charatsoft.com BMS export library v1.00\n" );
	fprintf( fp,"\n" );
	fprintf( fp,"#PLAYER %d\n",mBH.lPlayer );
	fprintf( fp,"#GENRE %s\n",mBH.mGenre );
	fprintf( fp,"#TITLE %s\n",mBH.mTitle );
	fprintf( fp,"#ARTIST %s\n",mBH.mArtist );
	fprintf( fp,"#BPM %5.2f\n",mBH.fBpm );
	fprintf( fp,"#PLAYLEVEL %d\n",mBH.lPlaylevel );

	if( strlen(mBH.mStagePic)>0 )	fprintf( fp,"#STAGEFILE %s\n",mBH.mStagePic );
	if( strlen(mBH.mMidifile)>0 )	fprintf( fp,"#MIDIFILE %s\n",mBH.mMidifile );

	fprintf( fp,"\n" );

	int i;
	char buf[1024];

	// WAVファイルの書き出し
	for( i=0;i<BMS_MAXBUFFER;i++ ) {
		if( mWavFile[i][0] ) {
			// NULLで無ければ書き出す
			itoa1016( i,buf,2 );
			fprintf( fp,"#WAV%s %s\n",buf,mWavFile[i] );
		}
	}
	fprintf( fp,"\n" );

	// BMPファイルの書き出し
	for( i=0;i<BMS_MAXBUFFER;i++ ) {
		if( mBmpFile[i][0] ) {
			// NULLで無ければ書き出す
			itoa1016( i,buf,2 );
			fprintf( fp,"#BMP%s %s\n",buf,mBmpFile[i] );
		}
	}
	fprintf( fp,"\n" );

	// 出力するチャンネルリスト
	static const int ch[] = {
		BMS_BACKMUSIC,
//		BMS_TEMPO,
		BMS_BACKANIME,
//		BMS_BPMINDEX,
		0x11,0x12,0x13,0x14,0x15,0x16,0x18,0x19,
		0x21,0x22,0x23,0x24,0x25,0x26,0x28,0x29,
		-1,
	};


	// データの書き出し
	int n = 0;
	int index;
	int line;
	char s[1024];
	char dst[1024];

	while( ch[n]!=-1 ) {

		index = 0;
		line = 0;

		// 全小節の処理
		while( index<iBmsData[ch[n]] ) {
			strcpy( s,"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" );

			// 現在の小節内のデータを処理
			while( index<iBmsData[ch[n]] ) {
				if( (line+1)*BMS_RESOLUTION<=pBmsData[ch[n]][index].lTime )
					break;

				// 時間から書き込み先アドレスを算出
				int addr = (int)(pBmsData[ch[n]][index].lTime - line*BMS_RESOLUTION);
				int fix_addr = (int)((float)addr / (BMS_RESOLUTION/192)) * 2;

				// 既に１つ前の情報があるか
				if( s[fix_addr]!='0' || s[fix_addr+1]!='0' ) {
					// 既にある場合は現在までのデータを書き込んでおく
					if( LineCompact(s,dst) )
						fprintf( fp,"#%03d%02X:%s\n",line,ch[n],dst );
					strcpy( s,"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" );
				}

				// データをセット
				itoa1016( pBmsData[ch[n]][index].lData,buf,2 );
				memcpy( &s[fix_addr],buf,2 );

				index++;
			}

			// 残りを書き出す
			if( strcmp(s,"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000")!=0 ) {
				if( LineCompact( s,dst ) ) {
					fprintf( fp,"#%03d%02X:%s\n",line,ch[n],dst );
				}
			}

			line++;
		}

		fprintf( fp,"\n" );

		n++;
	}

	fclose( fp );
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////
// 指定チャンネルのデータを昇順に並び替える
////////////////////////////////////////////////////////////////////////////////////////
BOOL BmsFile::Sort( int ch )
{
	if( ch<0 || ch>BMS_MAXBUFFER-1 )
		return FALSE;

	// 昇順に並び替える
	int i,j;
	for( i=0;i<iBmsData[ch]-1;i++ ) {
		for( j=i+1;j<iBmsData[ch];j++ ) {
			if( pBmsData[ch][i].lTime > pBmsData[ch][j].lTime ) {
				// 構造体を入れ替える
				BMSDATA dmy		= pBmsData[ch][i];		// ダミーに保存
				pBmsData[ch][i] = pBmsData[ch][j];		// iにjを入れる
				pBmsData[ch][j] = dmy;					// jにダミーを入れる
			}
		}
	}
	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////////////
// リスタート用にオブジェのフラグを元に戻す
////////////////////////////////////////////////////////////////////////////////////////
BOOL BmsFile::Restart( void )
{
	int i,j;
	for( j=0;j<BMS_MAXBUFFER;j++ ) {
		for( i=0;i<iBmsData[j];i++ ) {
			pBmsData[j][i].bFlag = TRUE;
		}
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////
// 時間からBMSカウント値を計算
////////////////////////////////////////////////////////////////////////////////////////
LONG BmsFile::GetCountFromTime( double sec )
{
	LONG cnt = 0;			// BMSカウント
	double t = 0;			// BMS上の時間
	double bpm = 130;
	
	if( iBmsData[BMS_TEMPO]>0 ) {
		bpm = pBmsData[BMS_TEMPO][0].fData;		// 初期BPM
	}

	if( sec<0 )
		return 0;

//	DEBUG( "■指定時間 (%.2f秒)\n",sec );

	// 指定時間を越えるまでタイムを加算
	int i;
	for( i=0;i<iBmsData[BMS_TEMPO];i++ ) {

		// １つ前の時間と新しい時間との経過時間から秒を算出
		double add = (double)( pBmsData[BMS_TEMPO][i].lTime - cnt ) / ( bpm / 60 ) / (BMS_RESOLUTION / 4);
//		DEBUG( "  [%d] 経過時間 %f秒\n",i,t+add );

		// 現在のテンポ値で時間が過ぎたら抜ける
		if( t+add>sec ) {
//			DEBUG( "                  └時間が過ぎた\n" );
			break;
		}

		t += add;										// 経過時間を加算
		bpm = (double)pBmsData[BMS_TEMPO][i].fData;		// 次のBPMをセット
		cnt = pBmsData[BMS_TEMPO][i].lTime;			// 計算済みのカウントをセット
	}

//	DEBUG( "  BPM %f\n",bpm );
//	DEBUG( "  CNT %I64d\n",cnt );

	// 指定時間と1つ前までの時間の差分
	double sub = sec - t;
//	DEBUG( "  差分 %f秒\n",sub );

	// 差分からBMSカウント数を算出
	LONG cnt2 = (LONG)(sub * (BMS_RESOLUTION / 4) * ( bpm / 60 ));

	// BMSカウント値に加算
	cnt += cnt2;
//	DEBUG( "  結果のカウント値 %I64d\n",cnt );

	return cnt;
}












////////////////////////////////////////////////////////////////////////////////////////
// 16進数文字列を数値に変換
////////////////////////////////////////////////////////////////////////////////////////
int BmsFile::atoi1610( const char *s )
{
	int ret = 0;			// 10進数に変換した値
	int i = 0;				// 参照する文字配列
	while( s[i] ) {
		if( !(s[i]>='0' && s[i]<='9') &&
			!(s[i]>='A' && s[i]<='Z') &&
			!(s[i]>='a' && s[i]<='z') )
			return 0;

		ret *= 16;				// 16倍
		int n = s[i] - '0';
		if( n>9 )
			n -= 7;
		if( n>15 )
			n -= 0x20;
		ret += n;
		i++;
	}
	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////
// 10進数を桁付きの16進数文字へ変換
////////////////////////////////////////////////////////////////////////////////////////
BOOL BmsFile::itoa1016( int num,char *dst,int keta )
{
	if( num<0 )
		return FALSE;

	itoa( num,dst,16 );

	// 小文字チェック
	int i;
	for( i=0;i<(int)strlen(dst);i++ ) {
		if( dst[i]>='a' && dst[i]<='z' ) {
			dst[i] -= 0x20;
		}
	}

	// 桁数指定の場合
	if( keta>=0 ) {
		// 桁数が足りない場合
		if( (int)strlen(dst)<keta ) {
			char dmy[1024];
			ZeroMemory( dmy,sizeof(dmy) );
			for( i=0;i<keta-(int)strlen(dst);i++ ) {
				dmy[i] = '0';			// 先頭に足りない分の0を追加
			}
			strcpy( &dmy[i],dst );		// その次に算出された文字列をつなげる
			strcpy( dst,dmy );			// 出力結果にダミー文字列をコピー		
		}
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////
// 1つのデータを追加
////////////////////////////////////////////////////////////////////////////////////////
BOOL BmsFile::AddData( int ch,LONG cnt,LONG data )
{
	// チャンネル番号をチェック
	if( ch<0 || ch>255 )
		return FALSE;

	// 小節長変更コマンドなら何もしない
	if( ch==BMS_STRETCH )
		return FALSE;

	// データが無ければ何もしない
	if( data==0 )
		return TRUE;

	switch( ch )
	{
	case BMS_BPMINDEX:
		// BPMのインデックス指定(新)
		iBmsData[BMS_TEMPO]++;
		pBmsData[BMS_TEMPO] = (LPBMSDATA)realloc( pBmsData[BMS_TEMPO],iBmsData[BMS_TEMPO]*sizeof(BMSDATA) );
		ZeroMemory( &pBmsData[BMS_TEMPO][ iBmsData[BMS_TEMPO]-1 ],sizeof(BMSDATA) );	// 追加した配列をクリア
		pBmsData[BMS_TEMPO][iBmsData[BMS_TEMPO]-1].bFlag = TRUE;
		pBmsData[BMS_TEMPO][iBmsData[BMS_TEMPO]-1].lTime = cnt;
		pBmsData[BMS_TEMPO][iBmsData[BMS_TEMPO]-1].lData = (LONG)mBH.fBpmIndex[data];	// テンポリストに入っているテンポ値を登録(LONG型にも保存)
		pBmsData[BMS_TEMPO][iBmsData[BMS_TEMPO]-1].fData = mBH.fBpmIndex[data];			// テンポリストに入っているテンポ値を登録
		break;
	default:
		// データを追加
		iBmsData[ch]++;
		pBmsData[ch] = (LPBMSDATA)realloc( pBmsData[ch],iBmsData[ch]*sizeof(BMSDATA) );
		ZeroMemory( &pBmsData[ch][ iBmsData[ch]-1 ],sizeof(BMSDATA) );					// 追加した配列をクリア
		pBmsData[ch][iBmsData[ch]-1].bFlag = TRUE;
		pBmsData[ch][iBmsData[ch]-1].lTime = cnt;
		pBmsData[ch][iBmsData[ch]-1].lData = data;
		pBmsData[ch][iBmsData[ch]-1].fData = (float)data;								// float型にも保存
		break;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////
// コマンド番号を返す
// 戻り値
//		0以上 : コマンド番号
//		-1    : オブジェ配置データ
//		-2    : 不明なコマンド
////////////////////////////////////////////////////////////////////////////////////////
int BmsFile::GetCommand( const char *s )
{
	static const char *command[13] = {
		"PLAYER",
		"GENRE",
		"TITLE",
		"ARTIST",
		"BPM",
		"MIDIFILE",
		"PLAYLEVEL",
		"RANK",
		"VOLWAV",
		"TOTAL",
		"StageFile",
		"WAV",
		"BMP",
	};

	// 検索ルーチン
	int i;
	for( i=0;i<13;i++ ) {
		if( strnicmp(s+1,command[i],strlen(command[i])) == 0)
			return i;	// コマンドならその番号を返す
	}

	// 先頭が'#nnncc'形式か
	BOOL obj = TRUE;
	for( i=0;i<5;i++ ) {
		if( s[i+1]<'0' || s[i+1]>'9' ) {
			obj = FALSE;
			break;
		}
	}

	// オブジェ配置なら -1
	if( obj ) {
		return -1;
	}

	// 処理不可能文字列なら
	return -2;
}

////////////////////////////////////////////////////////////////////////////////////////
// コマンドの文字列部分を返す（'\n'は削除 ':'も区切りとして処理）
////////////////////////////////////////////////////////////////////////////////////////
BOOL BmsFile::GetCommandString( const char *src,char *dst )
{
	int i = 0;
	int j = 0;

	// まずソースデータからデータ部分までのポインタを算出
	while(1) {
		if( src[i]==' ' || src[i]==0x09 || src[i]==':' ) {
			i++;
			break;
		}
		if( src[i]=='\n' || src[i]==NULL ) {
			return FALSE;
		}
		i++;
	}

	// 終端までをコピー
	while(1) {
		if( src[i]=='\n' || src[i]==NULL )
			break;
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = NULL;
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////
// BMSデータの読み込み
////////////////////////////////////////////////////////////////////////////////////////
BOOL BmsFile::LoadBmsData( const char *file )
{
	int i;
	char data[1024];
    int cmd;			// コマンド番号
	int line;			// 現在の小節番号
	int ch;				// 現在のチャンネル番号
    int len;			// 文字列の長さ


	FILE *fp;
	fp = fopen( file,"r" );
	if( !fp ) {
		sprintf( mLastError,"[%s] ファイルオープンエラー",file );
		return FALSE;
	}

	char buf[1024];
	while(1) {
		// １行を読みこむ
		ZeroMemory( buf,1024 );
		fgets( buf,1024,fp );
		if( buf[0]==NULL && feof(fp) )	// ファイルの終端なら検索終わり
			break;

//		DEBUG( "%s",buf );

		// コマンド以外なら次の行へ
		if( buf[0]!='#' )
			continue;

		// 最後の改行を消去
		if( buf[strlen(buf)-1]=='\n' )
			buf[strlen(buf)-1] = NULL;

		// コマンドの種類を取得
		cmd = GetCommand( buf );

		// オブジェ以外は全て無視
		if( cmd!=-1 )
			continue;

		// パラメータ文字列を取得
		ZeroMemory( data,1024 );
		if( !GetCommandString(buf,data) ) {
			fclose(fp);
			sprintf( mLastError,"[%s] パラメータ文字列取得エラー",buf );
			return FALSE;
		}
		
		// データであれば解析

		// チャンネル番号の取得
		char tmp[4];						// 汎用バッファ
		ZeroMemory( &tmp,sizeof(tmp) );
		tmp[0] = buf[4];					// チャンネル番号
		tmp[1] = buf[5];					// #001xx:******* のxx部分
		ch = atoi1610( tmp );				// 16進数

		// 小節の倍率変更命令の場合はキャンセル
		if( ch==BMS_STRETCH )	
			continue;

		// 小節番号を取得
		ZeroMemory( &tmp,sizeof(tmp) );
		memcpy( tmp,buf+1,3 );		// 小節部分を取得
		line = atoi( tmp );			// 数字化

		// データが存在するかチェック
		if( strlen(data)<1 ) {
			continue;
		}

		// データが偶数かチェック
		if( strlen(data)%2==1 ) {
			fclose( fp );
			sprintf( mLastError,"[%s] データが偶数個ではない",buf );
			return FALSE;
		}

		// データ数
		len = (int)strlen( data ) / 2;				
	
		// 現在の小節のカウント値から1音符分のカウント値を算出
		LONG tick = mBmsBar[line].lLength / len;

		// 実データを追加
		ZeroMemory( &tmp,sizeof(tmp) );
		for( i=0;i<len;i++ ) {
			tmp[0] = data[i*2];
			tmp[1] = data[i*2+1];
			int data = atoi1610( tmp );			// 16進数
			if( data>0 ) {
				// データが存在する場合
				AddData( ch, mBmsBar[line].lTime + (tick * i), data );
			}
		}
	}

	fclose( fp );

	// ソート
	for( i=0;i<BMS_MAXBUFFER;i++ )
		Sort( i );

/*	for( i=0;i<iBmsData[BMS_TEMPO];i++ ) {
		char s[256];
		sprintf( s,"[%08d] %f",(int)pBmsData[BMS_TEMPO][i].lTime,pBmsData[BMS_TEMPO][i].fData );
		DEBUG( "%s\n",s )
	}/**/

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////
// データを最適化して返す
////////////////////////////////////////////////////////////////////////////////////////
BOOL BmsFile::LineCompact( const char *src,char *dst )
{
	int i,j,k;
	char buf[1024];		// ワークバッファ
	strcpy( buf,src );	// 元データをコピー
	*dst = NULL;		// 出力先初期化

	// 010000020000030000040000010000020000030000040000010000020000030000040000010000020000030000040000
	//   ^^  ^^  ^^  ^^  ^^  ^^  ^^  ^^  ^^  ^^  ^^  ^^  ^^  ^^  ^^  ^^  ^^  ^^  ^^  ^^  ^^  ^^  ^^  ^^  i=1  (i+1)=2で割り切れる文字数か→○
	//   ^^^^  ^^^^  ^^^^  ^^^^  ^^^^  ^^^^  ^^^^  ^^^^  ^^^^  ^^^^  ^^^^  ^^^^  ^^^^  ^^^^  ^^^^  ^^^^  i=2  (i+1)=3で割り切れる文字数か→○
	//   ^^^^^^  ^^^^^^  ^^^^^^  ^^^^^^  ^^^^^^  ^^^^^^  ^^^^^^  ^^^^^^  ^^^^^^  ^^^^^^  ^^^^^^  ^^^^^^  i=3  (i+1)=4で割り切れる文字数か→○
	//   ^^^^^^^^  ^^^^^^^^  ^^^^^^^^  ^^^^^^^^  ^^^^^^^^  ^^^^^^^^  ^^^^^^^^  ^^^^^^^^  ^^^^^^^^  ^^^^  i=4  (i+1)=5で割り切れる文字数か→×
	//   ^^^^^^^^^^  ^^^^^^^^^^  ^^^^^^^^^^  ^^^^^^^^^^  ^^^^^^^^^^  ^^^^^^^^^^  ^^^^^^^^^^  ^^^^^^^^^^  i=5  (i+1)=6で割り切れる文字数か→○
	//   ^^^^^^^^^^^^  ^^^^^^^^^^^^  ^^^^^^^^^^^^  ^^^^^^^^^^^^  ^^^^^^^^^^^^  ^^^^^^^^^^^^  ^^^^^^^^^^  i=6  (i+1)=7で割り切れる文字数か→×
	//                                              ：
	//   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^      i=45 (i+1)=46で割り切れる文字数か→×
	//   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^    i=46 (i+1)=47で割り切れる文字数か→×
	//   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  i=47 (i+1)=48で割り切れる文字数か→○
	while(1) {

		// データ数を算出
		int l = (int)strlen( buf ) / 2;

		// 空文字ならデータ無し
		if( l==0 ) {
			return FALSE;
		}

		// 1個のデータなら
		if( l==1 ) {
			if( buf[0]=='0' && buf[1]=='0' ) {
				// 00ならデータ無し
				return FALSE;
			}
			// それ以外なら確定
			break;
		}


		// 2個以上なら最適化処理
		BOOL div = FALSE;					// 分割出来たか
		for( i=1;i<l;i++ ) {

			// 分割する文字数
			int fetch_size = 1 + i;

			// 割り切れるか
			if( (l%fetch_size)!=0 )
				continue;					// 割り切れないならスキップ

			// 分割文字数内の2番目以降に00以外が含まれるか
			BOOL zero = TRUE;		// 00以外が存在するか
			for( j=0;j<l;j+=fetch_size ) {
				for( k=1;k<fetch_size;k++ ) {
					int p = (j + k) * 2;
					if( buf[p]!='0' || buf[p+1]!='0' ) {
						// 00以外が存在するなら
						zero = FALSE;
						j = l;				// 上位ループも終わらせる
						break;
					}
				}
			}
			
			// 00のみなら現座時の分割サイズで分割
			if( zero ) {
				k = 1;
				for( j=0+fetch_size;j<l;j+=fetch_size ) {			// 1文字目は常に確定なので2つ目からコピー
					int src = j * 2;
					int dst = k * 2;
					buf[k*2+0] = buf[j*2+0];
					buf[k*2+1] = buf[j*2+1];
					// 次のコピー先へ
					k++;
				}
				buf[k*2] = NULL;
				l = k;
				div = TRUE;

//				DEBUG( "分割後 : %s\n",buf );
				break;
			}
		}

		// これ以上分割出来なかったら終わる
		if( !div )
			break;
	}

	// 結果を返す
	strcpy( dst,buf );

	return TRUE;
}
