//STΛCK: structs and functions
#include "stc.h"

stc* stcInit(int maxsize)
{
	stc *st = new stc;
	tp *ar = (tp*)calloc(maxsize, sizeof(tp));
	st->ar = ar;
	st->top = 0;
	st->maxsize = maxsize;
	return st;
}

int stcDestr(stc* st)
{
	st->top = 0;
	st->maxsize = 0;
	delete st;
	return 0;
}

int stcResize(stc* st)
{
	st->maxsize++;
	tp* sup = (tp*)realloc(st->ar, sizeof(tp) * st->maxsize);
	if (sup != NULL)
	{
		st->ar = sup;
		st->ar[st->maxsize] = 0;
	}
	else
	{
		stcDestr(st);
		delete sup;
		cout << "STACK OVERFLOW";
		exit(1);
	}
	return 0;
}

int stcPush(stc* st, int data)
{
	if (st->top == st->maxsize)
		stcResize(st);
	st->top++;
	st->ar[st->top - 1] = data;
	return 0;
}

int stcPop(stc* st)
{
	st->ar[st->top - 1] = 0;
	st->top--;
	return 0;
}

int stcDump(stc* st)
{
	cout << "STACK DUMP" << endl;
	cout << "stack size " << st->maxsize << endl;
	cout << "elements number " << st->top << endl;
	for (int i = 0; i < st->top; i++)
		cout << st->ar[i] << endl;
	cout << endl;
	return 0;
}