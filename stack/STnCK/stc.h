#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <iostream>
#include <cassert>
#include <typeinfo>
using namespace std;

typedef int stctype;

struct stack
{
	stctype* array;
	stctype* first;
	int size;
	int maxSize;
};
stack* stcInit(stack* stcToInit, int stackSize)
{
	stctype* array = (stctype*)calloc(stackSize, sizeof(stctype));
	stcToInit->maxSize = stackSize;
	stcToInit->size = 0;
	stcToInit->array = array;
	stcToInit->first = NULL;
	return stcToInit;
}
int stcResize(stack* stcToResize)
{
	stcToResize->maxSize++;
	stctype* newarr = (stctype*)realloc((void*)stcToResize->array, sizeof(stctype) * stcToResize->maxSize);
	stcToResize->array = newarr;
	return 0;
}
int stcPush(stack* stcToPush, stctype data)
{
	if (stcToPush->size == stcToPush->maxSize)
		stcResize(stcToPush);
	if (stcToPush->size == 0)
		stcToPush->first = stcToPush->array;
	else
		stcToPush->first++;
	*stcToPush->first = data;
	stcToPush->size++;
	return 0;
}
int stcPop(stack* stcToPop)
{
	stcToPop->size--;
	*stcToPop->first = NULL;
	stcToPop->first--;
	return 0;
}
int stcDump(stack* stcToDump)
{
	int* i = (int*)calloc(1, sizeof(int));
	for (int i = 0; i < stcToDump->maxSize; i++)
		cout << stcToDump->array[i] << '\n';
	return 0;
}