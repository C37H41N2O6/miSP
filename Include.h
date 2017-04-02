#pragma once

#include "Common.h"
#include "Calc.h"
#include "File.h"
#include "Window.h"

C_Calc		Calc;
C_File		File;
C_Window	Window;

int			miRNA_Type = 0;
V_STRING	FileList;
V_MIRNA		miRNA;
V_RESULT	Result;
int			Act_Flag = 0;
int			Result_Flag = 0;

int LoopCnt_1, LoopCnt_2, RNA_Num, miRNA_Num, Rate;