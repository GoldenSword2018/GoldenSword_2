//
//	Debug_Circle.cpp
//		Author:HIROMASA IKEDA		DATE:2018/07/06
//===============================================
#include"Debug_Circle.h"

//===============================================
//	マクロ定義
//===============================================
#define CIRCLE_VERTEX_COUNT (8)		//頂点数
#define CIRCLE_DRAW_MAX		(200)	//円の最大描画数

#define FVF_DEBUG_VERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

//===============================================
//	構造体
//===============================================
#if defined(_DEBUG) || defined(DEBUG)
typedef struct DebugVertex_tag
{
	D3DXVECTOR4 Position;
	D3DCOLOR	Color;

}DebugVertex;
#endif

//===============================================
//	グローバル変数
//===============================================
#if defined(_DEBUG) || defined(DEBUG)
static LPDIRECT3DVERTEXBUFFER9	g_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9	g_pIndexBuffer	= NULL;

static int g_CircleCounter	= 0;		//描画された円のカウント
static DebugVertex *g_pDebugVertex	= NULL;
static WORD *g_pDebugVertexIndex	= NULL;
#endif

//===============================================
//	初期化
//===============================================
void DebugPrimitive_Initialize(LPDIRECT3DDEVICE9 Device)
{
#if defined(_DEBUG) || defined(DEBUG)
	g_CircleCounter = 0;

	Device->CreateVertexBuffer(
		sizeof(DebugVertex) * CIRCLE_VERTEX_COUNT *CIRCLE_DRAW_MAX,	//データサイズ
		D3DUSAGE_WRITEONLY,	//頂点バッファへの書き込み専用
		FVF_DEBUG_VERTEX,	//FVF
		D3DPOOL_MANAGED,	
		&g_pVertexBuffer,
		NULL
	);

	Device->CreateIndexBuffer(
		sizeof(WORD) * CIRCLE_VERTEX_COUNT * 2 * CIRCLE_DRAW_MAX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIndexBuffer,
		NULL
	);
#else
	UNREFERENCED_PARAMETER(Device);
#endif
}

//===============================================
//	領域ロック
//===============================================
void DebugPrimitive_BatchBegin()
{
#if defined(_DEBUG) || defined(DEBUG)
	g_CircleCounter = 0;
	g_pVertexBuffer->Lock(0, 0, (void**)&g_pDebugVertex, 0);
	g_pIndexBuffer->Lock(0, 0, (void**)&g_pDebugVertexIndex, 0);
#endif
}

//===============================================
//	頂点登録
//===============================================
void DebugPrimitive_BatchDrawCircle(float x, float y, float radius)
{
#if defined(_DEBUG) || defined(DEBUG)
	//順
	int n = g_CircleCounter * CIRCLE_VERTEX_COUNT * 2;

	//角度差
	const float s = (D3DX_PI * 2) / CIRCLE_VERTEX_COUNT;

	//頂点追加
	for (int i = 0; i< CIRCLE_VERTEX_COUNT; i++)
	{
		g_pDebugVertex[n + i].Position.x = cosf(i * s) * radius + x;
		g_pDebugVertex[n + i].Position.y = sinf(i * s) * radius + y;
		g_pDebugVertex[n + i].Position.z = 1.0f;
		g_pDebugVertex[n + i].Position.w = 1.0f;
		g_pDebugVertex[n + i].Color = D3DCOLOR_RGBA(0, 255, 0, 255);
		g_pDebugVertexIndex[n * 2 + i * 2] = n + i;
		g_pDebugVertexIndex[n * 2 + i * 2 + 1] = n + (i + 1) % CIRCLE_VERTEX_COUNT;
	}
	g_CircleCounter++;
#else
	UNREFERENCED_PARAMETER(x);
	UNREFERENCED_PARAMETER(y);
	UNREFERENCED_PARAMETER(radius);
#endif
}

//===============================================
//	描画
//===============================================
void DebugPrimitive_BatchRun(LPDIRECT3DDEVICE9 Device)
{
#if defined(_DEBUG) || defined(DEBUG)
	g_pVertexBuffer->Unlock();
	g_pIndexBuffer->Unlock();

	Device->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(DebugVertex));
	Device->SetIndices(g_pIndexBuffer);
	Device->SetFVF(FVF_DEBUG_VERTEX);
	Device->SetTexture(0, NULL);
	Device->DrawIndexedPrimitive(D3DPT_LINELIST, 0, 0, CIRCLE_VERTEX_COUNT * CIRCLE_DRAW_MAX, 0, g_CircleCounter * CIRCLE_VERTEX_COUNT);
#else
	UNREFERENCED_PARAMETER(Device);
#endif
}

//===============================================
//	終了処理
//===============================================
void DebugPrimitive_Finalize()
{
#if defined(_DEBUG) || defined(DEBUG)
	if (g_pIndexBuffer)
	{
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}

	if (g_pVertexBuffer)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}
#endif
}