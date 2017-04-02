#pragma once

#include "Common.h"

class C_Window
{
	int		hFont[2];
	int		Save_Btn_def, Save_Btn_act, Save_Btn_push;
	int		Start_Btn_def, Start_Btn_act, Start_Btn_push;
	int		File_Btn_def, File_Btn_push;
	int		Radio_Btn_def, Radio_Btn_act;
	int		Pos_X, Pos_Y;

public:
	void Init(void);
	void Btn_Draw(int *Act_Flag, int *miRNA_Type);
	void Btn_Check(int *Act_Flag, int *miRNA_Type);
	void Str_Draw(V_STRING &FileList, const int Result_Flag);
	void Draw(int *Act_Flag, int *miRNA_Type, V_STRING &FileList, const int Result_Flag);
};