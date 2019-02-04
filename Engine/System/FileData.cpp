//
//	FileData.cpp
//		USER:HIROMASA IKEDA		DATE:2018/09/11
//===============================================
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"System.h"
#include"FileData.h"

//===============================================
//	グローバル変数
//===============================================
static FILE* pFile;

//===============================================
//	FileOpen	
//===============================================
bool File_Open(const char* FileName)
{
	pFile = NULL;
	pFile = fopen(FileName,"rb+");

	if(pFile == NULL)
	{
		MessageBox(*System_GethWnd(), "セーブファイルの読み込みに失敗しました。", "読み込み失敗", MB_OK);
		DestroyWindow(*System_GethWnd());
		return false;
	}

	return true;
}

//===============================================
//	File_SeekTop()
//===============================================
void File_SeekTop()
{
	fseek(pFile,0L,SEEK_SET);
}

//===============================================
//	File_Get()
//===============================================
FILE* File_Get()
{
	return pFile;
}

//===============================================
//	File_Close()
//===============================================
void File_Close()
{
	fclose(pFile);
}
