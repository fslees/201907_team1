//=============================================================================
//
// 譜面データ処理 [bms.h]
// Author : GP12A332_26_田中太陽
//
//=============================================================================
#ifndef _BMSFILE_H
#define _BMSFILE_H

#include <Windows.h>

#define BMS_RESOLUTION		9600			// 1小節のカウント値
#define BMS_MAXBUFFER		(16*16)			// 00～FFまでのバッファ数

// BMSチャンネル定義
#define BMS_BACKMUSIC		0x01			// その位置にきたら、自動的に再生されるWAVを指定します
#define BMS_STRETCH			0x02			// その小節の長さを定義したデータ倍します（１０進数、小数ともに使用可）
#define BMS_TEMPO			0x03			// 再生テンポ（ＢＰＭ / １分間の四分音符数）の途中変更（１６進数）
#define BMS_BACKANIME		0x04			// バックグラウンドアニメーション機能
#define BMS_EXTENEDOBJ		0x05			// 落下してくるオブジェを別のキャラクターナンバーのものにすり替える機能
#define BMS_CHGPOORANI		0x06			// POORを出したときに表示される画像を変更
#define BMS_LAYERANIME		0x07			// Ch.04で指定したBGAの上にかぶせるBMPを指定できます
#define BMS_BPMINDEX		0x08			// BPMのインデックス指定(新)


// BMSヘッダ情報
typedef struct _BMSHEADER {
	long		lPlayer;					// プレイモード
	char		mGenre[256];				// データのジャンル
	char		mTitle[256];				// データのタイトル
	char		mArtist[256];				// データの製作者
	float		fBpm;						// 初期テンポ(初期値は130)
	char		mMidifile[MAX_PATH];		// バックグラウンドで流すMIDIファイル
	long		lPlaylevel;					// ゲームの難易度
	long		lRank;						// 判定ランク
	long		lWavVol;					// 音量を元の何%にするか
	long		lTotal;						// ゲージの増量
	char		mStagePic[MAX_PATH];		// 曲開始字に表示する画像
	float		fBpmIndex[BMS_MAXBUFFER];	// テンポインデックス(初期値は120)

	long		lEndBar;					// 終了小節
	long		lMaxCount;					// 最大のカウント数
} BMSHEADER,*LPBMSHEADER;


// BMSデータ情報
typedef struct _BMSDATA {
	LONG		lTime;						// このデータの開始位置(BMSカウント値)
	LONG		lData;						// 鳴らすデータ(0x01～0xFF)
	float		fData;						// 小数値データ(テンポ用)
	BOOL		bFlag;						// アプリが使用出来る任意の変数(ここでは判定に利用)
} BMSDATA,*LPBMSDATA;


// 小節情報
typedef struct _BMSBAR {
	float		fScale;						// この小節の長さ倍率
	LONG		lTime;						// この小節の開始位置(BMSカウント値)
	LONG		lLength;					// この小節の長さ(BMSカウント値)
} BMSBAR,*LPBMSBAR;



////////////////////////////////////////////////////////////////////////////////////
// BMSクラス
////////////////////////////////////////////////////////////////////////////////////
class BmsFile {
protected:
	BMSHEADER	mBH;										// BMSヘッダ情報

	LPBMSDATA	pBmsData[BMS_MAXBUFFER];					// 実データ
	int			iBmsData[BMS_MAXBUFFER];					// 実データのそれぞれの数

	char		mWavFile[BMS_MAXBUFFER][MAX_PATH];			// WAVのファイル名
	char		mBmpFile[BMS_MAXBUFFER][MAX_PATH];			// BMPのファイル名

	BMSBAR		mBmsBar[1000+1];							// 小節データ(999小節時に1000番目も小節バーとして使うため+1しておく)

	char		mLastError[1024];							// エラーが発生した場合の文字列

public:
	BmsFile();												// コンストラクタ
	virtual ~BmsFile();										// デストラクタ

	// 基本メソッド
	BOOL Clear( void );										// データの初期化
	BOOL LoadHeader( const char *file );					// BMSヘッダ情報だけを取り出す
	BOOL Load( const char *file );							// BMSファイルのロード
	BOOL Save( const char *file );							// BMSファイルにセーブ
	BOOL Sort( int ch );									// 指定チャンネルのデータを昇順に並び替える

	BOOL Restart( void );									// リスタート用にオブジェのフラグを元に戻す
	LONG GetCountFromTime( double sec );					// 時間からBMSカウント値を計算

public:
	// 内部データのアクセス
	inline const char*			GetLastError( void )		{ return mLastError; }				// 最後のエラー文字列

	// ゲーム必須メソッド
	inline LONG					GetMaxCount( void )			{ return mBH.lMaxCount; }			// ゲーム内の最大のカウント値
	inline int					GetBarNum( void )			{ return mBH.lEndBar+1; }			// 小節バーの個数(最後の小節も含むため+1する)
	inline const LPBMSBAR		GetBar( int num )			{ return &mBmsBar[num]; }			// 小節バーのデータ
	inline int					GetObjeNum( int ch )		{ return iBmsData[ch]; }			// 指定チャネルのデータ数を返す
	inline const LPBMSDATA		GetObje( int ch,int num )	{ return &pBmsData[ch][num]; }		// チャネルと配列番号でデータを取得する
	inline const LPBMSHEADER	GetHeader( void )			{ return &mBH; }					// ヘッダ情報を返す
	inline const char*			GetBmpFile( int num )		{ return mBmpFile[num]; }			// 使用しているBMPファイル名
	inline const char*			GetWavFile( int num )		{ return mWavFile[num]; }			// 使用しているWAVファイル名

private:
	// 非公開関数
	int	 atoi1610( const char *s );							// 16進数文字列を数値に変換
	BOOL itoa1016( int num,char *dst,int keta=-1 );			// 10進数を桁付きの16進数文字へ変換
	BOOL AddData( int ch,LONG cnt,LONG data );				// 1つのデータを追加（ソートはされない）
	int	 GetCommand( const char *s );						// コマンド番号を返す
	BOOL GetCommandString( const char *src,char *dst );		// パラメータ文字列を取得
	BOOL LoadBmsData( const char *file );					// BMSデータの読み込み
	BOOL LineCompact( const char *src,char *dst );			// データを最適化して返す
};

#endif
