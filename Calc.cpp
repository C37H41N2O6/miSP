#include "Calc.h"
#include "File.h"

C_File F;

unsigned C_Calc::Calc_Launcher(void * Data)
{
	reinterpret_cast<C_Calc *>(Data)->Calc();
	return 0;
}

void C_Calc::Start(V_MIRNA &miRNA, V_STRING &FileList)
{
	Fin();

	copy(miRNA.begin(), miRNA.end(), back_inserter(Data_miRNA));
	copy(FileList.begin(), FileList.end(), back_inserter(Data_List));

	RNA_Num = Data_List.size()-1;
	LoopCnt_1_Max = Data_List.size();
	miRNA_Num = Data_miRNA.size();

	hTh = (HANDLE)_beginthreadex(NULL, 0, Calc_Launcher, this, 0, &thID);
}

void C_Calc::Calc(void)
{
	Result.clear();

	S_Result Buf;
		ZeroMemory(&Buf, sizeof(S_Result));
	const char *pos;
	int Addr;

	#pragma omp parallel for
		for (LoopCnt_1 = 1; LoopCnt_1 < LoopCnt_1_Max; LoopCnt_1++)
		{
			F.Read(Data_List, LoopCnt_1, &Data_RNA);
			for (LoopCnt_2 = 0; LoopCnt_2 < miRNA_Num; LoopCnt_2++)
			{
				Addr = -1;
				while ((pos = strstr(&Data_RNA.Array.c_str()[Addr + 1], Data_miRNA[LoopCnt_2].Array_Sence)) != NULL)
				{
					Addr = pos - Data_RNA.Array.c_str();
					Buf.FileName = Data_RNA.FileName;
					Buf.miRName = Data_miRNA[LoopCnt_2].Name;
					Buf.Type = "Sense";
					Buf.Pos = Addr;
					Result.push_back(Buf);
					ZeroMemory(&Buf, sizeof(S_Result));
				}

				Addr = -1;
				while ((pos = strstr(&Data_RNA.Array.c_str()[Addr + 1], Data_miRNA[LoopCnt_2].Array_Anti)) != NULL)
				{
					Addr = pos - Data_RNA.Array.c_str();
					Buf.FileName = Data_RNA.FileName;
					Buf.miRName = Data_miRNA[LoopCnt_2].Name;
					Buf.Type = "Anti_Sense";
					Buf.Pos = Addr;
					Result.push_back(Buf);
					ZeroMemory(&Buf, sizeof(S_Result));
				}

				Rate = ((LoopCnt_1-1)*miRNA_Num + LoopCnt_2+1) * 100 / (RNA_Num*miRNA_Num);
			}
		}
}

void C_Calc::Fin(void)
{
	CloseHandle(hTh);
}
