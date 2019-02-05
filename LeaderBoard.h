// ===============================================================================================
// プロジェクト名: 
// ファイル名: LeaderBoard.h
// 作成日 XX/XX/XXXX Author: Hashimoto Yuto AT12E-275-29                                       
// 追記:                                                                                        
// MM/DD/YYYY Author: ○○                                                                      
// ・××の変更〜〜〜〜                                                                         
// ===============================================================================================

#ifndef _LEADER_BOARD_H_
#define _LEADER_BOARD_H_
#pragma once

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// 
// インクルードファイル
// 
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

//
// Windows系
// 

// 
// 自作系
//

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// 
// 
// 
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
namespace LeaderBoard
{
void Init( void );
void SetNewScore( unsigned int NewScore );
void Update( void );
void Render( void );
void Finalize( void ); // 呼ぶと消えるぞ
}
/* +++++++++++++++ 注記<大> +++++++++++++++ */
/* ----- 注記<中> -----*/
// 注記<小>

#endif // _LEADER_BOARD_H_