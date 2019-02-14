// ===============================================================================================
// �v���W�F�N�g��: 
// �t�@�C����: LeaderBoard.cpp
// �T�v: 
// �쐬�� XX/XX/XXXX Author: Hashimoto Yuto AT12E-275-29                                       
// �ǋL:                                                                                        
// MM/DD/YYYY Author: ����                                                                      
// �E�~�~�̕ύX�`�`�`�`                                                                         
// ===============================================================================================

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// 
// �C���N���[�h�t�@�C��
// 
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
#include "LeaderBoard.h"
//
// Windows�n
// 
#include <vector>

// 
// ����n
//
#include "Score.h"
#include "Texture.h"
#include "Sprite.h"
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// 
// ���O���: LeaderBoard
// 
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
namespace LeaderBoard
{
const unsigned int RANKING_SCORE_MAX = 3; // �����L���O�ŕ\������X�R�A�̐�
// --------------------------------------------------------------------------------------
//
// �N���X: PersonalScore
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
// �R���X�g���N�^ �I�y���[�^�I�[�o�[���[�h �f�X�g���N�^
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
	// ����Null
}

//
// ���̑�
// 


// --------------------------------------------------------------------------------------
//
// �N���X: LeaderBoardModule
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
	void ScoreDraw( D3DXVECTOR2 _Pos, PersonalScore _Score );
};
LeaderBoardModule* LeaderBoardModule::pInstance = nullptr;

//
// �R���X�g���N�^ �I�y���[�^�I�[�o�[���[�h �f�X�g���N�^
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
// �Q�b�^�[
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
// �֐�
//
void LeaderBoardModule::ScoreDraw( D3DXVECTOR2 _Pos, PersonalScore _Score )
{
	int score = _Score.score;
	for( int i = 0; i < FIG; i++ )
	{
		unsigned int number = score % 10;
		score /= 10;
		Number_Render( { _Pos.x + ( NTexture::Get_Width( NTexture::ScoreTex ) * 0.1f ) * ( FIG - ( i + 1 ) ), _Pos.y }, number );
	}

}
void LeaderBoardModule::Render( void )
{
	D3DXVECTOR2 BoardPos = { WINDOWSCREEN_WIDTH_2, WINDOWSCREEN_HEIGHT_2 };
	NRender2D::Sprite(new Transform2(BoardPos, D3DXVECTOR2(1000.0f, 600.0f), 0.0f), new NTexture::NameTexture(NTexture::RankingBoard, { 0.0f,0.0f }, { 1.0f,1.0f }), D3DCOLOR_RGBA(255, 255, 255, 255));

	D3DXVECTOR2 NewScorePos = { 500.0f, 100.0f }; // ����̃X�R�A�̕\�����W
	D3DXVECTOR2 rankingScorePos = { 500.0f, 240.0f }; // �����L���O�̕\�����W

	// ����̃X�R�A
	if( pNewScore != nullptr )
	{
		ScoreDraw( NewScorePos, *pNewScore );
	}
	// �����L���O�̂Ƃ���
	float marginY = 80.0f;
	for( unsigned int sc = 0; sc < ( unsigned int ) ScoreCollection.size(); sc++ )
	{
		ScoreDraw( D3DXVECTOR2( rankingScorePos.x, rankingScorePos.y + marginY * sc ), ScoreCollection.at( sc ) );
	}
}
void LeaderBoardModule::Finalize()
{
	delete this;
}

//
// �v���C�x�[�g�֐�
//
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


	// �I���\�[�g
	// ����

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



	newScoreCollection.push_back( PersonalScore( *ScoreCollection.begin() ) );
	newScoreCollection.swap( ScoreCollection );
}

// --------------------------------------------------------------------------------------
//
// �]���s���̊֐�
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
/* +++++++++++++++ ���L<��> +++++++++++++++ */
/* ----- ���L<��> -----*/
// ���L<��>

/* ----- �֐��� XXXXXXXXXXXXXXXXXXXX ------------------------------------------------- */
/* �T�v XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  */
/* �߂�l: XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX�@�@�@�@�@�@�@�@�@�@�@*/
/* arg0: Type VariableName �T�v                                                        */
/* ----------------------------------------------------------------------------------- */

//ReturnType FunctionName( Type arg0... )
// {
//     /* ----- �����J�n ----- */
//     int XXXXX = NULL// �T�v
//     Func01() // ����T�v
//     a = Func02();
//         // �֐���
//         // �T�v: XXXX
//         // �ߒl: XXXXXX
//     Func03( arg0, // �^�@������ �T�v
//             arg1, // �^�@������ �T�v
//             arg2 );

// }