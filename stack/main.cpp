//#include "stack.h"
#include "stc.h"
#include <stdlib.h>
#include <cstring>



int main()
{
	cout << "STVCK v1.0 (c)mityabeldii, 2016" << '\n' << '\n';

	stack test = { NULL, NULL, NULL };
	stcInit(&test, 1);
	stcPush(&test, 1);
	stcPush(&test, 2);
	stcPush(&test, 3);
	stcPush(&test, 4);
	stcPop(&test);
	stcDump(&test);
	system("pause");
	return 0;
}