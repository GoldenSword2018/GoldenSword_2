//
//	FileData.h
//		Author:HIROMASA IKEDA	DATE:2018/09/11
//===============================================
#pragma once
#ifndef FILEDATA_H
#define FILEDATA_H

#include<stdio.h>

//===============================================
//	関数
//===============================================
bool File_Open(const char* FileName);	//ファイルの読み込み
void File_SeekTop();					//先頭にSeek
FILE* File_Get();						//ファイル取得
void File_Close();						//ファイルをクローズ

#endif // !FILEDATA_H




