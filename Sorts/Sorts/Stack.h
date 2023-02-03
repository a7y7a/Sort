#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>

typedef int STDataType;

typedef struct Stack
{
	STDataType* a;
	int top;
	int capacity;
}ST;

void STInit(ST* s);
void STPush(ST* s, STDataType x);
void STPop(ST* s);
STDataType STTop(ST* s);
int STSize(ST* s);
bool STEmpty(ST* s);
void STDestroy(ST* s);