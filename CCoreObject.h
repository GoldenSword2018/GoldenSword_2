//
//	CCoreObject.h
//		Author:HIROMASA IKEDA	DATE:2018/10/13
//===============================================
#pragma once
#ifndef COREOBJECT_H
#define COREOBJECT_H

#include<d3dx9.h>
#include<vector>
#include"common.h"

using namespace std;

// Hew
#include"CGameObject.h"
#include"CStageBlock.h"
#include"Collider.h"

//===============================================
//	��
//===============================================

//===============================================
//	CoreObject �N���X
//===============================================
class CoreObject:public NRender3D::CGameObject
{
public: 
	//����^�C�v
	enum CORE_DISCHARGE_JUDGE_TYPE
	{
		CORE_JUDGE_TYPE_0 = 0,
		CORE_JUDGE_TYPE_1,
		// enum max
		CORE_JUDGE__MAX
	};

	//�l�W�̌���
	enum CORE_DIRECTION
	{
		CORE_DIRECTION_FORWARD,
		CORE_DIRECTION_BEHIND,
		CORE_DIRECTION_UP,
		CORE_DIRECTION_DOWN,
		CORE_DIRECTION_RIGHT,
		CORE_DIRECTION_LEFT,
		// enum max
		CORE_DIRECTION_MAX
	};

private:	
	CORE_DISCHARGE_JUDGE_TYPE Type;		//��ѕ�����^�C�v
	
public:
	int BlockWidth;			// �u���b�N�ێ����i���j
	int BlockHeight;		// �u���b�N�ێ����i�c�j
	int BlockDepth;			// �u���b�N�ێ����i���s���j
	int NumBlocks;			// �u���b�N���ێ���

public:
	bool bHit;							// ��������
	D3DXVECTOR3 face;					// �l�W�O����
	D3DXVECTOR3 right;					// �l�W�E����
	D3DXVECTOR3 up;						// �l�W�����
	ShapeSphere ColShape;				// �l�W���g
	CORE_DIRECTION direction;
	void SetBlocks(int x, int y, int z);	// �l�W�Ƀu���b�N����������

public:
	CoreObject(CTransform* pTransform, AMesh* pMesh, CORE_DISCHARGE_JUDGE_TYPE Type, CORE_DIRECTION face);
	~CoreObject();
private:
	void SetFace(CORE_DIRECTION face);	// �l�W�̌����ݒ�

public:
	void Hit();			// ��������

	void Set_JudgeType(CORE_DISCHARGE_JUDGE_TYPE Type);	// ��ѕ��Z�b�g
	void Update();				// �X�V
	void Render();				// �`��
	void RenderBox();			// ����ڂĂ̕`��
	D3DXVECTOR3 GetFace();		// �l�W�̌����̎擾

};


//===============================================
//	CoreObjectManager �N���X
//===============================================

class CoreObjectManager
{
private:
	CoreObjectManager();
	~CoreObjectManager();
	static CoreObjectManager* pInstance;
public:
	static CoreObjectManager* GetInstance();
private:
	vector<CoreObject*> ppCoreCollection;
	CXModelMesh* pCoreModel;
public:
	void CreateCore( D3DXVECTOR3 pos, unsigned int x, unsigned int y, unsigned int z );
	unsigned int  GetCurrentCoreExist( void ) const;
	void UpdateCoreAll( void );
	void RenderCoreAll( void );
	void Finalize( void );
};
#endif // !CCOREOBJECT_H
