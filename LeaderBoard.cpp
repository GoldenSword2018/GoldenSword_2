// ===============================================================================================
// プロジェクト名: 
// ファイル名: LeaderBoard.cpp
// 概要: 
// 作成日 XX/XX/XXXX Author: Hashimoto Yuto AT12E-275-29                                       
// 追記:                                                                                        
// MM/DD/YYYY Author: ○○                                                                      
// ・××の変更～～～～                                                                         
// ===============================================================================================

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// 
// インクルードファイル
// 
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
#include "LeaderBoard.h"
//
// Windows系
// 
#include <vector>

// 
// 自作系
//
#include "Score.h"
#include "Texture.h"
#include "Sprite.h"
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// 
// 
// 
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
namespace LeaderBoard
{
const unsigned int RANKING_SCORE_MAX = 3; // ランキングで表示するスコアの数
// --------------------------------------------------------------------------------------
//
// クラス: PersonalScore
//
// --------------------------------------------------------------------------------------
class PersonalScore
{
public:
	PersonalScore();
	PersonalScore( unsigned int Score );
	PersonalScore( const PersonalScore& obj );
	PersonalScore& operator=( const PersonalScore& obj );
	~PersonalScore();
public:
	unsigned int score;
};

//
// コンストラクタ オペレータオーバーロード デストラクタ
//
PersonalScore::PersonalScore()
	:
	PersonalScore( 0 )
{

}

PersonalScore::PersonalScore( unsigned int _Score )
	:
	score( 0 )
{
	score = _Score;
}

PersonalScore::PersonalScore( const PersonalScore& obj )
{
	score = obj.score;
}

PersonalScore& PersonalScore::operator=( const PersonalScore& obj )
{
	if( this != &obj )
	{
		score = obj.score;
	}

	return *this;
}

PersonalScore::~PersonalScore()
{
	// 今はNull
}

//
// その他
// 


// --------------------------------------------------------------------------------------
//
// クラス: LeaderBoardModule
//
// --------------------------------------------------------------------------------------
class LeaderBoardModule
{
private:
	LeaderBoardModule();
	~LeaderBoardModule();
	static LeaderBoardModule* pInstance;
public:
	static LeaderBoardModule* GetInstance();
private:
	std::vector<PersonalScore> ScoreCollection;
	PersonalScore* pNewScore;
public:
	void Render( void );
	void SetNewScore( unsigned int NewScore );
	void Finalize();
private:
	void SortForRanking( void );
};
LeaderBoardModule* LeaderBoardModule::pInstance = nullptr;

//
// コンストラクタ オペレータオーバーロード デストラクタ
//
LeaderBoardModule::LeaderBoardModule()
{
	pNewScore = nullptr;
}

LeaderBoardModule::~LeaderBoardModule()
{
	if( 0 < ScoreCollection.size() )
	{
		ScoreCollection.clear();
	}

	if( pNewScore != nullptr )
	{
		delete pNewScore;
	}
}
//
// ゲッター
// 
LeaderBoardModule* LeaderBoardModule::GetInstance()
{
	if( pInstance == nullptr )
	{
		pInstance = new LeaderBoardModule();
	}

	return pInstance;
}
//
// 関数
//
void ScoreDraw( D3DXVECTOR2 _Pos, PersonalScore _Score )
{
	int score = _Score.score;
	for( int i = 0; i < FIG; i++ )
	{
		unsigned int number = _Score.score % 10;
		score /= 10;
		Number_Render( { _Pos.x + ( NTexture::Get_Width( NTexture::ScoreTex ) * 0.1f ) * ( FIG - ( i + 1 ) ), _Pos.y }, number );
	}
}
void LeaderBoardModule::Render( void )
{
	D3DXVECTOR2 NewScorePos = { 10.0f, 10.0f }; // 今回のスコアの表示座標
	D3DXVECTOR2 rankingScorePos = { 100.0f, 300.0f }; // ランキングの表示座標
	
	// 今回のスコア
	if( pNewScore != nullptr )
	{
		ScoreDraw( NewScorePos, *pNewScore );
	}
	// ランキングのところ
	float marginY = NTexture::Get_Height(NTexture::ScoreTex);
	for( unsigned int sc = 0; sc < ( unsigned int ) ScoreCollection.size(); sc++ )
	{
		ScoreDraw( D3DXVECTOR2( rankingScorePos.x, rankingScorePos.y + marginY * sc ), ScoreCollection.at( sc ) );
	}
}
void LeaderBoardModule::Finalize()
{
	delete this;
}
void LeaderBoardModule::SetNewScore( unsigned int _NewScore )
{
	if( pNewScore == nullptr )
	{
		pNewScore = new PersonalScore( _NewScore );
	}
		
	pNewScore->score = _NewScore;
	
	ScoreCollection.push_back( PersonalScore( _NewScore ) );
	SortForRanking();
}

void LeaderBoardModule::SortForRanking( void )
{
	std::vector<PersonalScore> newScoreCollection;


	// 選択ソート
	// 準備

	int ci = 0;
	int dh = 0;
	unsigned int maxIte;
	PersonalScore tmp;
	int cnt = 0;
	PersonalScore maxScore;

	while( (size_t) 1 < ScoreCollection.size() )
	{
		maxScore = ScoreCollection.at( 0 );
		maxIte = 0;
		for( unsigned int sc = 0; sc < ScoreCollection.size(); sc++ )
		{
			if( maxScore.score  < ScoreCollection.at( sc ).score )
			{
				maxScore = ScoreCollection.at( sc );
				maxIte = sc;
			}
			
		}

		newScoreCollection.push_back( PersonalScore( maxScore ) );
		ScoreCollection.erase( ScoreCollection.begin() + maxIte );
	}


	if( (size_t) 1 < ScoreCollection.size() )
	{
		// チェック用
	}

	newScoreCollection.push_back( PersonalScore( *ScoreCollection.begin() ) );
	newScoreCollection.swap( ScoreCollection );
}

// --------------------------------------------------------------------------------------
//
// 余所行きの関数
//
// --------------------------------------------------------------------------------------
void Init( void )
{
	LeaderBoardModule::GetInstance();
}

void SetNewScore( unsigned int _NewScore )
{
	LeaderBoardModule::GetInstance()->SetNewScore( _NewScore );
}

void Render( void )
{
	LeaderBoardModule::GetInstance()->Render();
}

void Finalize( void )
{
	LeaderBoardModule::GetInstance()->Finalize();
}

}
/* +++++++++++++++ 注記<大> +++++++++++++++ */
/* ----- 注記<中> -----*/
// 注記<小>

/* ----- 関数名 XXXXXXXXXXXXXXXXXXXX ------------------------------------------------- */
/* 概要 XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  */
/* 戻り値: XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX　　　　　　　　　　　*/
/* arg0: Type VariableName 概要                                                        */
/* ----------------------------------------------------------------------------------- */

//ReturnType FunctionName( Type arg0... )
// {
//     /* ----- 処理開始 ----- */
//     int XXXXX = NULL// 概要
//     Func01() // 動作概要
//     a = Func02();
//         // 関数名
//         // 概要: XXXX
//         // 戻値: XXXXXX
//     Func03( arg0, // 型　引数名 概要
//             arg1, // 型　引数名 概要
//             arg2 );

// }