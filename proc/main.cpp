#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

const char PUSH_CODE = 1;
const char ADD_CODE = 2;
const char END_CODE = 3;
const char MOV_CODE = 4;
const char JMP_CODE = 5;
const char DUMPST_CODE = 6;
const char AX_CODE = -1;
const char BX_CODE = -2;

int const PUSH_AR = 1;
int const ADD_AR = 0;
int const END_AR = 0;
int const MOV_AR = 2;
int const JMP_AR = 0;
int const DUMPST_AR = 0;

struct stc
{
	double* ar;
	int top;
	int size;
};

stc* initst(int size)
{
	double* ar = (double*)calloc(size, sizeof(double));
	stc* st = new stc;
	st->ar = ar;
	st->size = size;
	st->top = 0;
	return st;
}

int destr(stc* st)
{
	delete st;
	return 0;
}

int resizest(stc* st)
{
	st->size *= 2;
	double* qw = (double*)realloc(st, sizeof(double*) * st->size);
	if (qw != NULL)
		st->ar = qw;
	else
	{
		cout << "st overflow" << endl;
		system("pause");
		exit(1);
	}
	return 0;
}

int push(stc* st, double a)
{
	if (st->top == st->size)
		resizest(st);
	st->ar[st->top++] = a;
	return 0;
}

int pop(stc* st)
{
	if (st->top == 0)
	{
		cout << "st overflow" << endl;
		system("pause");
		exit(1);
	}
	st->ar[st->top] = 0;
	st->top--;
	return 0;
}

int dump(stc* st)
{
	cout << "dump" << endl;
	for (int i = 0; i < st->top; i++)
		cout << st->ar[i] << endl;
	return 0;
}

char code(char comand[20])
{
	if ((!strcmp(comand, "PUSH")) || (!strcmp(comand, "push")))
		return PUSH_CODE;
	if ((!strcmp(comand, "ADD")) || (!strcmp(comand, "add")))
		return ADD_CODE;
	if ((!strcmp(comand, "END")) || (!strcmp(comand, "end")))
		return END_CODE;
	if ((!strcmp(comand, "MOV")) || (!strcmp(comand, "mov")))
		return MOV_CODE;
	if ((!strcmp(comand, "JMP")) || (!strcmp(comand, "jmp")))
		return JMP_CODE;
	if ((!strcmp(comand, "DUMPST")) || (!strcmp(comand, "dumpst")))
		return DUMPST_CODE;
	return 1;
}

int arg(char comand[20])
{
	if ((!strcmp(comand, "PUSH")) || (!strcmp(comand, "push")))
		return PUSH_AR;
	if ((!strcmp(comand, "ADD")) || (!strcmp(comand, "add")))
		return ADD_AR;
	if ((!strcmp(comand, "END")) || (!strcmp(comand, "end")))
		return END_AR;
	if ((!strcmp(comand, "MOV")) || (!strcmp(comand, "mov")))
		return MOV_AR;
	if ((!strcmp(comand, "JMP")) || (!strcmp(comand, "jmp")))
		return JMP_AR;
	if ((!strcmp(comand, "DUMPST")) || (!strcmp(comand, "dumpst")))
		return DUMPST_AR;
	return 0;
}

int decode(FILE* in, char comand[20], char buffer[], int& bs, int&bms)
{
	buffer[bs] = code(comand);
	bs++;
	int a = arg(comand);
	while (a > 0)
	{
		a--;
		if (code(comand) == PUSH_CODE)
		{
			char sup[20] = "";
			fscanf(in, "%s", sup);
			if (!strcmp(sup, "AX"))
				buffer[bs] = AX_CODE;
			else
			if (!strcmp(sup, "BX"))
				buffer[bs] = BX_CODE;
			else
			{
				int f = stoi(sup, nullptr, 0);
				*(int*)(buffer + bs) = f;
			}
			bs++;
		}
		if (code(comand) == MOV_CODE)
		{
			char sup[20] = "", to[20] = "";
			fscanf(in, "%s", sup);
			if (((!strcmp(sup, "AX")) || (!strcmp(sup, "AX,"))) || ((!strcmp(sup, "ax")) || (!strcmp(sup, "ax,"))))
				buffer[bs] = AX_CODE;
			else
			if (((!strcmp(sup, "BX")) || (!strcmp(sup, "BX,"))) || ((!strcmp(sup, "bx")) || (!strcmp(sup, "bx,"))))
				buffer[bs] = BX_CODE;
			else
			{
				int f = stoi(sup, nullptr, 0);
				*(int*)(buffer + bs) = f;
			}
			bs++;
		}
		if (code(comand) == JMP_CODE)
		{
		}
	}
	return 0;
}

int ass(char fin[20], char fout[20])
{
	FILE* in = fopen(fin, "r");
	FILE* out = fopen(fout, "w");

	char comand[20] = "";
	int bs = 0;
	int bms = 1000;
	char* buffer = (char*)calloc(bms, sizeof(char));
	while (!feof(in))
	{
		fscanf(in, "%s", comand);
		decode(in, comand, buffer, bs, bms);
	}

	fprintf(out, "%d %d", bs, bms);
	fwrite(buffer, sizeof(char), bms, out);

	fclose(in);
	fclose(out);
	return 0;
}

struct pr
{
	double AX;
	double BX;
	double CX;
	double DX;
	stc* st;
	int ip;
};

int go(char stream[], pr* cp)
{
	//cout << (int*)code << endl;
	switch (stream[cp->ip])
	{
	case PUSH_CODE:
	{
		cp->ip++;
		if ((stream[cp->ip] == AX_CODE) || (stream[cp->ip] == BX_CODE))
		{
			if (stream[cp->ip] == AX_CODE)
				cp->AX = cp->st->ar[cp->st->top - 1];
			if (stream[cp->ip] == BX_CODE)
				cp->BX = cp->st->ar[cp->st->top - 1];
			pop(cp->st);
		}
		else
			push(cp->st, (double)stream[cp->ip]);
		break;
	}
	case END_CODE:
	{
		system("pause");
		return 0;
	}
	case DUMPST_CODE:
	{
		dump(cp->st);
		break;
	}
	case MOV_CODE:
	{
		char to = stream[cp->ip + 1], from = stream[cp->ip + 2];
		double arg = 0;
		if (from == AX_CODE)
			arg = cp->AX;
		else
			if (from == BX_CODE)
				arg = cp->BX;
			else
				arg = (double)from;
		if (to == BX_CODE)
			cp->BX = arg;
		if (to == AX_CODE)
			cp->AX = arg;
		cp->ip += 2;
		break;
	}
	}
	return 0;
}

int cpu(char fin[20])
{
	FILE* in = fopen(fin, "r");
	pr* cp = new pr;
	stc* st = initst(1000);
	cp->st = st;
	int ss = 0, sms = 0;
	fscanf(in, "%d %d", &ss, &sms);
	char* stream = (char*)calloc(sms, sizeof(char) * 1);
	*stream = fread(stream, ss, sizeof(char), in);
	for (cp->ip = 0; cp->ip < ss; cp->ip++)
		go(stream, cp);

	delete cp;
	fclose(in);
	return 0;
}

int main()
{
	cout << "CPU, mityabeldii, 2016" << endl;

	ass("program.txt", "stream.txt");
	cpu("stream.txt");

	system("pause");
	return 0;
}
