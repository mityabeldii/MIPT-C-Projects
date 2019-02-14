#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <conio.h>
#include "stc.h"
#include "asm.h"
using namespace std;

struct proc
{
	stc* stack;
	tp AX;
	tp BX;
	tp CX;
	tp DX;
	tp FX;
	tp EX;
};

char* resize(char stream[20], int ss, int &sms)
{
	sms++;
	char* asmSupportBuffer = (char*)realloc(stream, sizeof(char) * sms);
	stream = asmSupportBuffer;
	return stream;
}

int operate(char stream[20], int &i, proc mproc, stc* RAM)
{
	switch (stream[i])
	{
		case CODE_PUSH:
		{
			i++;
			char sup = (char)stream[i];
			if (sup == CODE_PUSH_AX)
			{
				mproc.AX = mproc.stack->ar[mproc.stack->top - 1];
				stcPop(mproc.stack);
				break;
			}
			tp data = (int)stream[i];
			stcPush(mproc.stack, data);
			break;
		}
		case CODE_ADD:
		{
			stcPush(RAM, mproc.stack->ar[mproc.stack->top - 1]);
			stcPop(mproc.stack);
			stcPush(RAM, mproc.stack->ar[mproc.stack->top - 1]);
			stcPop(mproc.stack);
			stcPush(mproc.stack, RAM->ar[RAM->top - 1] + RAM->ar[RAM->top - 2]);
			stcPop(RAM);
			stcPop(RAM);
			break;
		}
		case CODE_POP:
		{
			stcPop(mproc.stack);
			break;
		}
		case CODE_DUMPST:
		{
			stcDump(mproc.stack);
			break;
		}
		case CODE_END:
		{
			system("pause");
			//exit(1);
			break;
		}
		case CODE_MUL:
		{
			stcPush(RAM, mproc.stack->ar[mproc.stack->top - 1]);
			stcPop(mproc.stack);
			stcPush(RAM, mproc.stack->ar[mproc.stack->top - 1]);
			stcPop(mproc.stack);
			stcPush(mproc.stack, RAM->ar[RAM->top - 1] * RAM->ar[RAM->top - 2]);
			stcPop(RAM);
			stcPop(RAM);
			break;
		}
		//default	exit(1);
	}
	return 0;
}

int cpu(char file[20])
{
	FILE* in = fopen(file, "r");
	stc* RAM = stcInit(1000);
	int ss = 0, sms = 1, i = 0;
	proc mproc = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};
	stc* stack = stcInit(1);
	mproc.stack = stack;

	fscanf(in, "%d\n%d\n", &ss,&sms);
	char* stream = (char*)calloc(sms, sizeof(char) * 1);
	*stream = fread(stream, ss, sizeof(char), in);
	while (i < ss)
	{
		operate(stream, i, mproc, RAM);
			i++;
	}
	stcDestr(mproc.stack);
	return 0;
}

int main()
{
	assembler("p.myasm", "cpuStream.stream");
	cpu("cpuStream.stream");
	//system("pause");
	return 0;
}