//STΛCK header file
#include <cstdlib>
#include <iostream>

using namespace std;

typedef int tp;

struct stc
{
	tp* ar;
	int top;
	int maxsize;
};

stc* stcInit(int maxsize);
int stcDestr(stc* st);
int stcResize(stc* st);
int stcPush(stc* st, int data);
int stcPop(stc* st);
int stcDump(stc* st);