#pragma once

#include "Common.h"
#include <Shlobj.h>
#pragma comment(lib, "Ole32.lib")

static int __stdcall BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);

class C_File
{

public:
	void Folder_Open(V_STRING *FileList, int def = 0);
	void Folder_Select(char *path);
	void Save(const V_RESULT &Result);
	void Import(V_MIRNA *miRNA, int Type);
	void Read(const V_STRING &FileList, int Num, S_RNA *RNA);
};