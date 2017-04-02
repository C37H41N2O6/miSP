#pragma once

#include "Common.h"
#include <process.h>

class C_Calc
{
	int LoopCnt_1_Max;
	V_MIRNA		Data_miRNA;
	V_STRING	Data_List;
	S_RNA		Data_RNA;

	unsigned int thID;
	HANDLE hTh;

public:
	static unsigned __stdcall Calc_Launcher(void *Data);
	void Start(V_MIRNA &miRNA, V_STRING &FileList);
	void Calc(void);
	void Fin(void);
};