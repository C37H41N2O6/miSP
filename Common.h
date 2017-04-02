#pragma once

#include "DxLib.h"
#include "Struct.h"
#include "Style.h"

#include <algorithm>
#include <iterator>
#include <locale.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <Windows.h>

typedef vector<string>		V_STRING;
typedef vector<S_miRNA>		V_MIRNA;
typedef vector<S_Result>	V_RESULT;

extern V_RESULT	Result;
extern int LoopCnt_1, LoopCnt_2, RNA_Num, miRNA_Num, Rate;
