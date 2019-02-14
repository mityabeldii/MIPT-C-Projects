/**
> name		> STΛCK
> file		> stack.h
> authors	> Mitya Beldii, GROUP 672, MIPT
> date		> DECEMBER 12, 2016
> version	> 1.1
**/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <cassert>

using namespace std;

//Set of error codes
const int OK = 0;
const int ERROR = 1;
const int STACK_UNDERFLOW = 2;
const int STACK_OVERFLOW = 3;
const int WRONG_NUMBER = 4;

struct node
{
	int data;
	node* next;
};

struct stack
{
	int currentSize;
	int maxSize;
	node* first;
};

/*
	@stackPush - funtion to push one element into top of stack
	(struct stack)	$stackToPush - stack to push
	(int)			$dataToPush - data of new element
					return OK
*/
int stackPush(stack* stackToPush, int dataToPush);
/*
	@stackPop - funtion to take one element from the top of stack
	(struct stack)	$stackToPush - stack to pop
					return OK
*/
int stackPop(stack* stackToPop);
/*
	@stackDump - function
	(struct stack)	$stackToDump - stack to dump
					return OK
*/
int stackDump(stack* stackToDump);
/*
	@stackOk - function that is checking stack for different errors
	(struct stack)	$stackToCheck - stack to checking
					return OK
					return ERROR
					return WRONG_NUMBER
*/
int stackOk(stack* stackToCheck);
/*
	@stackConstruct - initialization of stack
	(struct stack)	$stackToConstruct - stack to init
	(int)			$&maxSize - number of elements if stack
					return OK
*/
int stackConstruct(stack* stackToConstruct, int &maxSize);
/*
	@stackDestruct - function to destruct stack
	(struct stack)	$stackToDestruct - stack to destruct
					return OK
*/
int stackDestruct(stack* stackToDestruct);
/*
	@stackDumpToFile - function that dumps file into the file
	(struct stack)  $stackToDump 	- stack that dumps
	(int)			$output 		- file to print
*/
int stackDumpToFile(stack* stackToDump, FILE *output);

int stackPush(stack* stackToPush, int dataToPush)
{
	assert(&stackToPush);
	assert(&dataToPush);
	assert(stackOk(stackToPush) == OK);
	if (stackToPush->currentSize == stackToPush->maxSize)
	{
		/*
		cout << "STACK OVERFLOW" << '\n';
		cout << "ERROR " << STACK_OVERFLOW << " while pop" << '\n' << '\n';
		return STACK_OVERFLOW;\
		*/
		stackToPush->maxSize++;
	}
	node* supportNode = new node;

	supportNode->data = dataToPush;
	supportNode->next = stackToPush->first;
	stackToPush->first = supportNode;
	stackToPush->currentSize++;	
	//memory cleaning
	supportNode = NULL;
	delete supportNode;
	assert(stackOk(stackToPush) == OK);
	return OK;
}


int stackPop(stack* stackToPop)
{
	assert(&stackToPop);
	assert(stackOk(stackToPop) == OK);
	//checking if stack is empty
	if (stackToPop->currentSize == 0)
	{
		cout << "STACK UNDERFLOW " << '\n';
		cout << "ERROR " << STACK_UNDERFLOW << " while pop" << '\n' << '\n';
		return STACK_UNDERFLOW;
	}

	node* supportNode = new node;

	supportNode->next = stackToPop->first;
	stackToPop->first = stackToPop->first->next;
	stackToPop->currentSize--;
	//memory cleaning
	delete supportNode->next;
	supportNode = NULL;
	delete supportNode;
	assert(stackOk(stackToPop) == OK);
	return OK;
}

int stackDump(stack* stackToDump)
{
	assert(&stackToDump);
	assert(stackOk(stackToDump) == OK);

	cout << "STACK DUMP" << '\n';
	//checking if stack is empty
	if (stackToDump->currentSize == 0)
	{
		cout << "stack is empty" << '\n' << '\n';
		return STACK_UNDERFLOW;
	}
	//dumping stack information
	cout << "current stack size - " << stackToDump->currentSize << '\n';
	cout << "max stack size - " << stackToDump->maxSize << '\n' << '\n';
	cout << "STACK ELEMENTS DUMP" << '\n';

	//dumping elements
	node* supportNode = new node;
	supportNode = stackToDump->first;
	while (supportNode->next != NULL)
	{
		cout << "data " << supportNode->data << '\n';
		cout << "current" << &supportNode << '\n';
		cout << "next " << supportNode->next << '\n';
		cout << '\n';
		supportNode = supportNode->next;
	}
	//dumping last element
	cout << "data " << supportNode->data << '\n';
	cout << "current" << &supportNode << '\n';
	cout << "next " << supportNode->next << '\n' << '\n';
	//memory cleaning
	supportNode = NULL;
	delete supportNode;
	assert(stackOk(stackToDump) == OK);
	return OK;
}

int stackOk(stack* stackToCheck)
{
	assert(stackToCheck);

	node* supportNode = new node;
	int counter = 0;
	supportNode->next = stackToCheck->first;
	//counting elements
	while (supportNode->next != NULL)
	{
		counter++;
		supportNode = supportNode->next;
		//checking if stack wasn't initialized
		if (unsigned int(supportNode) == 0xcdcdcdcd)
		{
			cout << "ERROR: stack wasn't initialized" << '\n';
			system("pause");
			exit(1);
		}
	}
	//comparing number of elements in stack
	if (counter != stackToCheck->currentSize)
	{
		cout << "ERROR " << WRONG_NUMBER << '\n';
		cout << "number of elements and it's value are not equal" << '\n';
		supportNode = NULL;
		delete supportNode;
		return WRONG_NUMBER;
	}
	//memory cleaning
	supportNode = NULL;
	delete supportNode;
	return OK;
}

int stackConstruct(stack* stackToConstruct, int &maxSize)
{
	assert(&stackToConstruct != NULL);
	assert(maxSize > 0);
	stackToConstruct->currentSize = 0;
	stackToConstruct->maxSize = maxSize;
	stackToConstruct->first = NULL;
	assert(stackOk(stackToConstruct) == OK);
	return OK;
}


int stackDestruct(stack* stackToDestruct)
{
	assert(&stackToDestruct != NULL);
	assert(stackOk(stackToDestruct) == OK);
	//pop all elements before memory cleaning
	while (stackToDestruct->currentSize > 0)
		stackPop(stackToDestruct);
	stackToDestruct->currentSize = NULL;
	stackToDestruct->maxSize = NULL;
	stackToDestruct->first = NULL;
	assert(stackOk(stackToDestruct) == OK);
	return OK;
}

int stackDumpToFile(stack* stackToDump, FILE *output)
{
	//checking if stack is empty
	if (stackToDump->currentSize == 0)
	{
		fprintf(output, "stack is empty\n\n");
		return STACK_UNDERFLOW;
	}
	stack* stack2 = new stack;
	int size = 3;
	stackConstruct(stack2, size);

	fprintf(output, "STACK DUMP\n");
	fprintf(output, "current stack size - %d\n", stackToDump->currentSize);
	fprintf(output, "max stack size - %d\n\n", stackToDump->maxSize);
	fprintf(output, "STACK ELEMENTS DUMP\n");

	while (stackToDump->currentSize > 0)
	{
		fprintf(output, "data %d\n", stackToDump->first->data);
		fprintf(output, "current %d\n", &stackToDump->first);
		fprintf(output, "next %d\n", &stackToDump->first->next);
		fprintf(output, " - - -\n");

		stackPush(stack2, stackToDump->first->data);
		stackPop(stackToDump);
	}
	while (stack2->currentSize > 0)
	{
		stackPush(stackToDump, stack2->first->data);
		stackPop(stack2);
	}
	stackDestruct(stack2);
	delete stack2;
	return OK;
}