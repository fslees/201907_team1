//======================================
// �m�[�c�̕`�揈��[noteview.cpp]
// Author : ����@�W��
//======================================
#include "noteview.h"
#include "note.h"

//=====================================
//�O���[�o���ϐ�
//=====================================
LPD3DXBUFFER		D3DXBuffMatNote;	    // �}�e���A�����ւ̃|�C���^
DWORD				NumMatNote;				// �}�e���A�����̐�
LPD3DXMESH			D3DXMeshNote;		    // ���b�V�����ւ̃|�C���^
LPDIRECT3DTEXTURE9	D3DTextureNote;			// �e�N�X�`���ւ̃|�C���^


//=====================================
//�R���X�g���N�^
//=====================================
NoteView::NoteView()
{
	//������
	LPD3DXBUFFER		D3DXBuffMatNote = NULL;	    // �}�e���A�����ւ̃|�C���^
	DWORD				NumMatNote = 0;				// �}�e���A�����̐�
	LPD3DXMESH			D3DXMeshNote = NULL;		// ���b�V�����ւ̃|�C���^
	LPDIRECT3DTEXTURE9	D3DTextureNote = NULL;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(NOTE_MODEL,			// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
								D3DXMESH_SYSTEMMEM,		// ���b�V���̍쐬�I�v�V�������w��
								pDevice,				// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
								NULL,					// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
								&D3DXBuffMatNote,		// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
								NULL,					// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
								&NumMatNote,			// D3DXMATERIAL�\���̂̐�
								&D3DXMeshNote)))		// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
	{
		E_FAIL;
	}

}

//=====================================
//�f�X�g���N�^
//=====================================
NoteView :: ~NoteView()
{
	if (D3DTextureNote != NULL)
	{// �e�N�X�`���̊J��
		D3DTextureNote->Release();
		D3DTextureNote = NULL;
	}

	if (D3DXMeshNote != NULL)
	{// ���b�V���̊J��
		D3DXMeshNote->Release();
		D3DXMeshNote = NULL;
	}

	if (D3DXBuffMatNote != NULL)
	{// �}�e���A���̊J��
		D3DXBuffMatNote->Release();
		D3DXBuffMatNote = NULL;
	}
}

//=====================================
//�`�揈��
//=====================================
void NoteView::Draw()
{
	//Note�������Get
	D3DXVECTOR3 pos = note->GetPos();
	D3DXVECTOR3 scl = note->GetScl();
	D3DXMATRIX  mtxWorld = note->GetMtxWorld();

	//
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	// ��]�𔽉f(����͉�]�Ȃ�)
	/*D3DXMatrixRotationYawPitchRoll(&mtxRot, note->rot.y, note->rot.x, note->rot.z);
	D3DXMatrixMultiply(&note->mtxWorld, &note->mtxWorld, &mtxRot);*/

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, pos.x,pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A�����ɑ΂���|�C���^���擾
	pD3DXMat = (D3DXMATERIAL*)D3DXBuffMatNote->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)NumMatNote; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, D3DTextureNote);

		// �`��
		D3DXMeshNote->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}

