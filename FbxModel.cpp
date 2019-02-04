//
//	FbxModel.cpp
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	インクルード	include
//===============================================
#include"common.h"

#include"FbxModel.h"

//===============================================
//	マクロ定義		define
//===============================================


//===============================================
//	グローバル変数	global
//===============================================
namespace fbx
{
	//------------------------------------
	//	グローバル変数
	//------------------------------------
	FbxManager* g_lpManager = NULL;	//マネージャー

	//------------------------------------
	//	初期化処理
	//------------------------------------
	int Initialize()
	{
		//Fbxマネージャの初期化
		g_lpManager = FbxManager::Create();

		//初期化失敗
		if (g_lpManager == NULL) return 1;

		FbxScene* Scene = LoadScene(g_lpManager,"", "Fight Idle.fbx");

		LoadModel(Scene);

		return 0;
	}

	//------------------------------------
	//	終了処理
	//------------------------------------
	int Finalize()
	{
		if (g_lpManager != NULL)
		{
			g_lpManager->Destroy();
			g_lpManager = NULL;
		}

		return 0;
	}

	//ロード
	FbxScene* LoadScene(FbxManager* Manager, const char* Name, const char* FilePath)
	{
		//入出力設定を作成
		FbxIOSettings* lpIos = FbxIOSettings::Create(Manager, IOSROOT);

		//入出力設定を適応
		Manager->SetIOSettings(lpIos);

		//FBXインポータの初期化
		FbxImporter* lpImporter = FbxImporter::Create(Manager, "");

		//FBX読み込み
		if (!lpImporter->Initialize(FilePath, -1, Manager->GetIOSettings()))
		{
			Manager->Destroy();

			return NULL;
		}

		//シーンの初期化
		FbxScene* Scene = FbxScene::Create(Manager, Name);

		//シーンのインポート
		if (!lpImporter->Import(Scene)) return NULL;

		//インポータの削除
		lpImporter->Destroy();

		//三角ポリゴン変換
		FbxGeometryConverter geometryConberter(Manager);
		geometryConberter.Triangulate(Scene, true);

		return Scene;
	}

	//------------------------------------
	//	ノード取得
	//------------------------------------
	FbxNode* GetNode(const FbxScene* Scene)
	{
		FbxNode* rootNode = Scene->GetRootNode();

		if (rootNode != NULL) return NULL;

		return rootNode;
	}

	int MeshNum(const FbxScene* Scene)
	{
		return Scene->GetSrcObjectCount<FbxMesh>();
	}

	//------------------------------------
	//	モデル情報
	//------------------------------------
	void LoadModel(FbxScene* Scene)
	{
		FbxNode* node = FbxNode::Create(Scene,"");		//ノード
		FbxMesh* mesh = FbxMesh::Create(Scene,"");
		//FbxMesh* mesh = Scene->GetRootNode()->GetMesh();	//メッシュ

		int PolygonNum = mesh->GetPolygonCount();			//ポリゴン数
		int VertexNum = mesh->GetControlPointsCount();		//頂点数
		int IndexNum = mesh->GetPolygonVertexCount();		//インデックス数
		FbxVector4* vertex = mesh->GetControlPoints();		//頂点座標

		D3DXVECTOR4* Position = new D3DXVECTOR4[VertexNum];	//頂点

		//各頂点設定
		for(int i = 0; i < VertexNum; i++)
		{
			Position[i].x = vertex[i][0];
			Position[i].y = vertex[i][1];
			Position[i].z = vertex[i][2];
			Position[i].w = vertex[i][3];
		}

		//頂点インデックス
		int* index = mesh->GetPolygonVertices();	
		int* indexBuffer = new int[IndexNum];
		for(int i = 0; i < IndexNum; i++)
		{
			indexBuffer[i] = index[i];
		}

		D3DXVECTOR3* Normal;		//法線
		int NormalLayerNum = mesh->GetElementNormalCount();	//法線セット数
		for(int i = 0; i < NormalLayerNum; i++)
		{
			FbxGeometryElementNormal* NormalSet = mesh->GetElementNormal(i);		//法線セット
			FbxGeometryElement::EMappingMode Mapping = NormalSet->GetMappingMode();//マッピングモード
			FbxGeometryElement::EReferenceMode Refarence = NormalSet->GetReferenceMode();	//リファレンスモード

			if(Mapping ==  FbxGeometryElement::eByControlPoint)
			{
				if(Refarence == FbxGeometryElement::eDirect)
				{
					int NormalCount = NormalSet->GetDirectArray().GetCount();
					Normal = new D3DXVECTOR3[NormalCount];

					FbxVector4* At = &NormalSet->GetDirectArray().GetAt(i);
					for(int i = 0; i < NormalCount; i++)
					{
						
						Normal[i].x = At[i][0];
						Normal[i].y = At[i][1];
						Normal[i].z = At[i][2];
					}
				}
			}
		}
	}
}
