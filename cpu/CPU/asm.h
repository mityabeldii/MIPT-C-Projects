#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "asmCodes.h"
using namespace std;

int asmComandGroup(char asmCommand[20]);
char asmComandCode(char asmCommand[20]);
char* asmBufferResize(char asmBuffer[20], int asmBufferSize, int &asmBufferMaxSize);
int asmCommandDecode(FILE* in, char asmCommand[20], char asmBuffer[20], int &asmBufferSize, int &asmBufferMaxSize);
char* assembler(char codeFileName[20], char streamFileName[20]);