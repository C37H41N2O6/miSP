#include "Window.h"

void C_Window::Init(void)
{
	SetOutApplicationLogValidFlag(FALSE);
	SetMainWindowText("mips");
	ChangeWindowMode( TRUE );
	SetDrawScreen( DX_SCREEN_BACK );
	SetGraphMode( 400, 240, 32 );
	SetBackgroundColor(245, 245, 245);
	SetAlwaysRunFlag( TRUE );
	DxLib_Init();

	hFont[0] = CreateFontToHandle("TimesNewRoman", 15, 4, DX_FONTTYPE_ANTIALIASING);
	hFont[1] = CreateFontToHandle("TimesNewRoman", 15, 6, DX_FONTTYPE_ANTIALIASING);

	SetDXArchiveExtension("btn");

	Start_Btn_def = LoadGraph("ui\\00.png");
	Start_Btn_act = LoadGraph("ui\\01.png");
	Start_Btn_push = LoadGraph("ui\\02.png");
	Save_Btn_def = LoadGraph("ui\\03.png");
	Save_Btn_act = LoadGraph("ui\\04.png");
	Save_Btn_push = LoadGraph("ui\\05.png");
	File_Btn_def = LoadGraph("ui\\06.png");
	File_Btn_push = LoadGraph("ui\\07.png");
	Radio_Btn_def = LoadGraph("ui\\08.png");
	Radio_Btn_act = LoadGraph("ui\\09.png");
}

void C_Window::Btn_Draw(int *Act_Flag, int *miRNA_Type)
{
	Btn_Check(Act_Flag, miRNA_Type);

	DrawGraph(PosX_Save, PosY_Save, Save_Btn_def, TRUE);
	DrawGraph(PosX_Start, PosY_Start, Start_Btn_def, TRUE);
	DrawGraph(PosX_File, PosY_File, File_Btn_def, TRUE);
	DrawGraph(PosX_Radio, PosY_Radio, Radio_Btn_def, TRUE);
	DrawGraph(PosX_Radio+170, PosY_Radio, Radio_Btn_def, TRUE);

	switch (*Act_Flag)
	{
		case 1:
			DrawGraph(PosX_Start, PosY_Start, Start_Btn_act, TRUE);
			break;
		case 2:
			DrawGraph(PosX_Start, PosY_Start, Start_Btn_push, TRUE);
			break;
		case 3:
			DrawGraph(PosX_Save, PosY_Save, Save_Btn_act, TRUE);
			break;
		case 4:
			DrawGraph(PosX_Save, PosY_Save, Save_Btn_push, TRUE);
			break;
		case 5:
			DrawGraph(PosX_File, PosY_File, File_Btn_push, TRUE);
			break;
	}

	switch (*miRNA_Type)
	{
		case 0:
			DrawGraph(PosX_Radio, PosY_Radio, Radio_Btn_act, TRUE);
			break;
		case 1:
			DrawGraph(PosX_Radio+170, PosY_Radio, Radio_Btn_act, TRUE);
			break;
	}
}

void C_Window::Btn_Check(int *Act_Flag, int *miRNA_Type)
{
	GetMousePoint(&Pos_X, &Pos_Y);
	if ((PosY_Save <= Pos_Y) && (Pos_Y <= PosY_Save+SizeY_Save-1))
	{
		if ((PosX_Save <= Pos_X) && (Pos_X <= PosX_Save+SizeX_Save-1))
		{
			if ((GetMouseInput() && MOUSE_INPUT_LEFT) != 0)
			{
				*Act_Flag = 4;
			}
			else
			{
				*Act_Flag = 3;
			}
		} else if ((PosX_Start <= Pos_X) && (Pos_X <= PosX_Start + SizeX_Start - 1))
		{
			if ((GetMouseInput() && MOUSE_INPUT_LEFT) != 0)
			{
				*Act_Flag = 2;
			}
			else
			{
				*Act_Flag = 1;
			}
		}
		else
		{
			*Act_Flag = 0;
		}
	} else if ((PosY_File <= Pos_Y) && (Pos_Y <= PosY_File+SizeY_File-1))
	{
		if ((PosX_File <= Pos_X) && (Pos_X <= PosX_File + SizeX_File - 1))
		{
			if ((GetMouseInput() && MOUSE_INPUT_LEFT) != 0)
			{
				*Act_Flag = 5;
			}
		}
		else
		{
			*Act_Flag = 0;
		}
	}
	else
	{
		*Act_Flag = 0;
	}
	if ((PosY_Radio <= Pos_Y) && (Pos_Y <= PosY_Radio + SizeY_Radio - 1))
	{
		if ((PosX_Radio <= Pos_X) && (Pos_X <= PosX_Radio + SizeX_Radio + 110))
		{
			if ((GetMouseInput() && MOUSE_INPUT_LEFT) != 0)
			{
				*miRNA_Type = 0;
			}
		}
		else if ((PosX_Radio + 170 <= Pos_X) && (Pos_X <= PosX_Radio + SizeX_Radio + 255))
		{
			if ((GetMouseInput() && MOUSE_INPUT_LEFT) != 0)
			{
				*miRNA_Type = 1;
			}
		}
	}
}

void C_Window::Str_Draw(V_STRING & FileList, const int Result_Flag)
{
	DrawStringToHandle(20, PosY_File + 10, "Search Folder", GetColor(0, 0, 0), hFont[0]);
	DrawStringToHandle(PosX_Radio + SizeX_Radio + 10, PosY_Radio - 1, "mature-miRNA", GetColor(0, 0, 0), hFont[0]);
	DrawStringToHandle(PosX_Radio + SizeX_Radio + 180, PosY_Radio - 1, "pre-miRNA", GetColor(0, 0, 0), hFont[0]);

	switch (Result_Flag)
	{
		case 2:
			DrawStringToHandle(PosX_Done, PosY_Done, "ŒvŽZŠ®—¹", GetColor(0, 0, 0), hFont[1]);
			break;
		case 4:
			DrawStringToHandle(PosX_Done, PosY_Done, "•Û‘¶Š®—¹", GetColor(0, 0, 0), hFont[1]);
			break;
	}

	if (FileList.size() > 0)
	{
		DrawFormatStringToHandle(40, PosY_File + SizeY_File + 5, GetColor(0, 0, 0), hFont[0], "%s", FileList[0].c_str());
	}
	if ((Rate != 100) && (Rate != 0))
	{
		DrawFormatStringToHandle(140, PosY_Done, GetColor(0, 0, 0), hFont[1], "progress : %d%%", Rate);
	}
}

void C_Window::Draw(int *Act_Flag, int *miRNA_Type, V_STRING &FileList, const int Result_Flag)
{
	Btn_Draw(Act_Flag, miRNA_Type);
	Str_Draw(FileList, Result_Flag);
}