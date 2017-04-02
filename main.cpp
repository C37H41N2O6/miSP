#include "Include.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Window.Init();
	File.Folder_Open(&FileList, 1);

	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();
			switch (Act_Flag)
			{
				case 2:
					File.Import(&miRNA, miRNA_Type);
					Calc.Start(miRNA, FileList);
					break;
				case 4:
					File.Save(Result);
					RNA_Num = 0;
					Result_Flag = 4;
					break;
				case 5:
					File.Folder_Open(&FileList);
					break;
			}

			if ((RNA_Num*miRNA_Num) != 0)
			{
				if (Rate == 100)
				{
					Result_Flag = 2;
				}
				else
				{
					Result_Flag = 0;
				}
			}
			else
			{
				Rate = 0;
			}

			Window.Draw(&Act_Flag, &miRNA_Type, FileList, Result_Flag);
		ScreenFlip();
	}

	Calc.Fin();
	return 0;
}