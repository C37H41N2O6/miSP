#include "File.h"

void C_File::Folder_Open(V_STRING *FileList, int def)
{
	char path[MAX_PATH];
		ZeroMemory(path, MAX_PATH);
	char cDir[MAX_PATH];
		ZeroMemory(cDir, MAX_PATH);

	switch (def)
	{
		case 0:
			strcpy_s(cDir, MAX_PATH, (*FileList)[0].c_str());
			FileList->clear();
			C_File::Folder_Select(path);
			break;
		case 1:
			GetCurrentDirectory(MAX_PATH, path);
			strcat_s(path, MAX_PATH, "\\data");
			break;
	}
	FileList->push_back(path);
	strcat_s(path, sizeof(path), "\\*.txt");

	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile(path, &fd);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			do
			{
				FileList->push_back(fd.cFileName);
			} while (FindNextFile(hFind, &fd));
		}
		else
		{
			FileList->pop_back();
		}
	FindClose(hFind);

	if (strcmp((*FileList)[0].c_str(),"") == 0)
	{
		FileList->clear();
		FileList->push_back(cDir);
	}
}

int __stdcall BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	if (uMsg == BFFM_INITIALIZED)
	{
		SetWindowText(hwnd, _T("テストのダイアログ"));
		SendMessage(hwnd, BFFM_SETSELECTION, FALSE, lpData);
	}
	else
	{
		char chText[MAX_PATH];
		if (SHGetPathFromIDList((LPITEMIDLIST)lParam, chText))
			SendMessage(hwnd, BFFM_SETSTATUSTEXT, TRUE, (LPARAM)chText);
	}

	return 0;
}
void C_File::Folder_Select(char *path)
{
	char			chPutFolder[MAX_PATH];
	LPITEMIDLIST	pidlRetFolder;
		ZeroMemory(&pidlRetFolder, sizeof(pidlRetFolder));

	BROWSEINFO		stBInfo;
		ZeroMemory(&stBInfo, sizeof(stBInfo));
		stBInfo.pidlRoot = NULL;
		stBInfo.hwndOwner = 0;
		stBInfo.pszDisplayName = chPutFolder;
		stBInfo.lpszTitle = "フォルダを選択してください";
		stBInfo.lpfn = BrowseCallbackProc;
		stBInfo.lParam = 0L;
		stBInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_EDITBOX | BIF_VALIDATE | BIF_NEWDIALOGSTYLE;

	pidlRetFolder = SHBrowseForFolder(&stBInfo);

	if (pidlRetFolder != NULL)
	{
		SHGetPathFromIDList(pidlRetFolder, path);
		CoTaskMemFree(pidlRetFolder);
	}
}

void C_File::Save(const V_RESULT &Result)
{
	char FileName_Full[MAX_PATH];
		strcpy_s(FileName_Full, MAX_PATH, "test.csv");
	char FileName[MAX_PATH];
		ZeroMemory(FileName, MAX_PATH);

	OPENFILENAME ofn;
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = GetMainWindowHandle();
		ofn.lpstrFilter = _T("csv(*.csv)\0*.csv\0\0");
		ofn.lpstrFile = FileName_Full;
		ofn.lpstrFileTitle = FileName;
		ofn.nMaxFile = sizeof(FileName_Full);
		ofn.nMaxFileTitle = sizeof(FileName);
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
		ofn.lpstrTitle = _T("ファイルを開く");
		ofn.lpstrDefExt = _T("csv");

	if (GetSaveFileName(&ofn) == TRUE)
	{
		FILE *sf;
		fopen_s(&sf, FileName_Full, "w");
			for (int i = 0; i < Result.size(); i++)
			{
				fprintf(sf, "%s,%s,%d,%s\n", Result[i].FileName.c_str(), Result[i].miRName.c_str(), Result[i].Pos, Result[i].Type.c_str());
			}
		fclose(sf);
	}
}

void C_File::Import(V_MIRNA *miRNA, int Type)
{
	FILE	*lf;
	char	StrBuf[512];
	char	*FileName = "";
	S_miRNA Buf;
		ZeroMemory(&Buf, sizeof(S_miRNA));
	switch (Type)
	{
		case 0:
			FileName = "miRNA.txt";
			break;
		case 1:
			FileName = "pre-miRNA.txt";
			break;
	}

	miRNA->clear();

	fopen_s(&lf, FileName, "r" );
		int Total = 0;
		while( fgets(StrBuf,512,lf) != NULL )
		{
			switch( Total )
			{
				case 0:
					sscanf_s( StrBuf, ">%s %*s %*s %*s %*s", Buf.Name, 64);
					break;
				case 1:
					sscanf_s(StrBuf, "%s", Buf.Array_Sence, 64);
					Buf.SeqLen = strlen(Buf.Array_Sence);
					for (int i = 0; i < Buf.SeqLen; i++)
					{
						if (Buf.Array_Sence[i] == 'T')
						{
							Buf.Array_Sence[i] = 'U';
						}
					}

					for (int i = 0; i<64; i++)
					{
						int j = Buf.SeqLen - i - 1;
						if (Buf.Array_Sence[j] == 'G')
						{
							Buf.Array_Anti[i] = 'C';
						}
						else if (Buf.Array_Sence[j] == 'U')
						{
							Buf.Array_Anti[i] = 'A';
						}
						else if (Buf.Array_Sence[j] == 'A')
						{
							Buf.Array_Anti[i] = 'U';
						}
						else if (Buf.Array_Sence[j] == 'C')
						{
							Buf.Array_Anti[i] = 'G';
						}
					}

					miRNA->push_back( Buf );

					ZeroMemory( StrBuf, 512 );
					ZeroMemory( &Buf, sizeof(S_miRNA) );
					break;
			}
			Total = 1 - Total;
		}
	fclose( lf );
}

void C_File::Read(const V_STRING &FileList, int Num, S_RNA *RNA)
{
	FILE *lf;
	char FileName[MAX_PATH];
	char Chara;

	ZeroMemory(RNA, sizeof(RNA));
	sprintf_s(FileName, MAX_PATH, "%s\\%s", FileList[0].c_str(), FileList[Num].c_str());

	fopen_s(&lf, FileName, "r");
		while ((Chara = fgetc(lf)) != EOF)
		{
			if (Chara != '\n')
			{
				if (Chara == 'T')
				{
					Chara = 'U';
				}

				RNA->Array.push_back(Chara);
			}
		}
		RNA->FileName = FileList[Num];
		RNA->SeqLen = RNA->Array.size();
	fclose(lf);
}