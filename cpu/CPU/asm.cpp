#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "stc.h"
#include "asmCodes.h"
using namespace std;

int asmComandGroup(char asmCommand[20])
{
	if (!strcmp(asmCommand, "PUSH"))
		return GROUP_PUSH;
	if (!strcmp(asmCommand, "ADD"))
		return GROUP_ADD;
	if (!strcmp(asmCommand, "END"))
		return GROUP_END;
	if (!strcmp(asmCommand, "POP"))
		return GROUP_POP;
	if (!strcmp(asmCommand, "DUMPST"))
		return GROUP_DUMPST;
	if (!strcmp(asmCommand, "MUL"))
		return GROUP_MUL;
	return -1;
}

char asmComandCode(char asmCommand[20])
{
	if (!strcmp(asmCommand, "PUSH"))
		return CODE_PUSH;
	if (!strcmp(asmCommand, "ADD"))
		return CODE_ADD;
	if (!strcmp(asmCommand, "END"))
		return CODE_END;
	if (!strcmp(asmCommand, "POP"))
		return CODE_POP;
	if (!strcmp(asmCommand, "DUMPST"))
		return CODE_DUMPST;
	if (!strcmp(asmCommand, "AX"))
		return CODE_PUSH_AX;
	if (!strcmp(asmCommand, "MUL"))
		return CODE_MUL;
	return -1;
}

char* asmBufferResize(char asmBuffer[20], int asmBufferSize, int &asmBufferMaxSize)
{
	asmBufferMaxSize++;
	char* asmSupportBuffer = (char*)realloc(asmBuffer, sizeof(char) * asmBufferMaxSize + 1);
	asmBuffer = asmSupportBuffer;
	return asmBuffer;
}


int asmCommandDecode(FILE* in, char asmCommand[20], char asmBuffer[20], int &asmBufferSize, int &asmBufferMaxSize)
{
	if (asmBufferSize == asmBufferMaxSize)
		asmBuffer = asmBufferResize(asmBuffer, asmBufferSize, asmBufferMaxSize);
	if (asmComandCode(asmCommand) != -1)
	{
		asmBuffer[asmBufferSize] = asmComandCode(asmCommand);
		asmBufferSize++;
		int a = asmComandGroup(asmCommand);
		while (a > 0)
		{
			if (asmBufferSize == asmBufferMaxSize)
				asmBuffer = asmBufferResize(asmBuffer, asmBufferSize, asmBufferMaxSize);
			int arg = 0;
			char asmCommand[20] = "";
			fscanf(in, "%s", asmCommand);
			if (!strcmp(asmCommand, "AX"))
				asmBuffer[asmBufferSize] = asmComandCode(asmCommand);
			else
			{
				int arg = stoi(asmCommand, nullptr, 0);
				*(int*)(asmBuffer + asmBufferSize) = arg;
			}
			asmBufferSize++;
			a--;
		}
	}
	return 0;
}

char* assembler(char codeFileName[20], char streamFileName[20])
{
	FILE* in = fopen(codeFileName, "r");
	FILE* out = fopen(streamFileName, "w");
	char asmCommand[20] = "empty";
	int asmBufferSize = 0, asmBufferMaxSize = 100;
	char* asmBuffer = (char*)calloc(asmBufferMaxSize, sizeof(char) * 1);
	while (!feof(in))
	{
		fscanf(in, "%s", asmCommand, 20);
  		asmCommandDecode(in, asmCommand, asmBuffer, asmBufferSize, asmBufferMaxSize);
	}
	fprintf(out, "%d\n%d\n", asmBufferSize, asmBufferMaxSize);
	fwrite(asmBuffer, asmBufferSize, sizeof(char), out);
	fclose(in);
	fclose(out);
	return asmBuffer;
}