#pragma once
#include <string>

using namespace std;

struct S_miRNA
{
	char	Name[64];
	char	Array_Sence[64];
	char	Array_Anti[64];
	int		SeqLen;
};

struct S_RNA
{
	string	FileName;
	string	Array;
	int		SeqLen;
};

struct S_Result
{
	string	FileName;
	string	miRName;
	string	Type;
	int		Pos;
};