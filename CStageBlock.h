//
//	CStageBlock.h
//		Author:YU NISHIMAKI		DATE:2018/11/13
//===============================================
//	�ύX�� Changed By
//		Name:YU NISHIMAKI		DATE:2019/02/05
//
//-----------------------------------------------

#pragma once
#ifndef CSTAGE_BLOCK_H
#define CSTAGE_BLOCK_H

//================================================
//	�C���N���[�h	include
//================================================
#include"common.h"
#include<d3dx9.h>
#include<vector>
#include"Texture.h"

//Class
#include"CGameObject.h"
#include"Collider.h"
#include"CCoreObject.h"

// �����蔻��
class ShapeOBB;

//================================================
//	�}�N����`	define
//================================================
#define NUM_STAGE_VERTEX		(24)
#define FVF_STAGE_BLOCK_VERTEX	( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )		// �\����StageBlockVertex��FVF�t���O
#define STAGE_BLOCK_SPEED		(1.0f)
#define MARGIN					(60)
#define WEIGHT					(1)


//================================================
//	�񋓌^		enum
//================================================
enum DISCHARGING_TYPE
{
	FALL,		// ��������
	RADIALLY,	// ���ˏ��

	NONE
};

//================================================
//	�\����		struct/typedef
//================================================
typedef struct StageBlockVertex_tag
{
	D3DXVECTOR3 Position;			// ���_���W
	D3DXVECTOR3 Normal;				// �@���x�N�g��
	D3DCOLOR Color;					// ���_�F
	D3DXVECTOR2 TexCoord;			// �e�N�X�`�����W
}StageBlockVertex;


//================================================
//	�O���[�o���ϐ��@global
//================================================


//================================================
//	�N���X		class
//================================================


//-------------------------------------
//	StageBlock�N���X
//-------------------------------------
class StageBlock:public NRender3D::CGameObject
{
	//-------------------------------------
	//	�`��֌W
	//-------------------------------------
private:
	LPDIRECT3DTEXTURE9 pTexture;	// �u���b�N�ɓ\��e�N�X�`���|�C���^

// �o�b�t�@�p�ϐ�
private:
	static LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;			// ���_�o�b�t�@
	static LPDIRECT3DINDEXBUFFER9 pIndexBuffer;				// �C���f�b�N�X�o�b�t�@

	static StageBlockVertex *pVertex;
	static WORD *pVertexIndex;

public:
	static void Initialize();		// ������(���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�̊m��)
	static void Finalize();			// �I������(���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�̉��)

	//-------------------------------------
	//	�o���o���֌W
	//-------------------------------------
private: // ���
	D3DXVECTOR3 Speed;	// ������ё��x

public: // �o���o�� �C�x���g�p
	DISCHARGING_TYPE Discharging_Type;	// ������ѕ��̃^�C�v
	int DelayFrameForDrop;				// �o���o���ɂȂ��Ĕ��ł����܂ł̎���

public: // �o���o��
	void SetSpeed(D3DXVECTOR3 CorePosition, int CoreType);

public: // ��ʊ֐�
	void Set_DischargingType(DISCHARGING_TYPE Type);

//===========================================================//

public:
	StageBlock* pPrev;
	StageBlock* pNext;
public:
	// �R���X�g���N�^
	StageBlock(CTransform *pTransform, NTexture::Name TextureIndex);
	StageBlock(CTransform* pTransform, NTexture::Name TextureIndex, DISCHARGING_TYPE type);

	void Update();					// �X�V
public:
	void Render();					// �`��

};


#endif