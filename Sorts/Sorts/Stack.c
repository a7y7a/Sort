#define _CRT_SECURE_NO_WARNINGS 1
#include"Stack.h"

void STInit(ST* s)
{
	assert(s);
	s->a = NULL;
	s->top = s->capacity = 0;
}

void STPush(ST* s, STDataType x)
{
	assert(s);
	if (s->top == s->capacity)
	{
		int newCapacity = s->capacity ? 2 * s->capacity : 4;
		STDataType* tmp = (STDataType*)realloc(s->a, sizeof(STDataType)*newCapacity);
		if (tmp)
		{
			s->a = tmp;
			s->capacity = newCapacity;
		}
		else
		{
			printf("realloc fail\n");
			exit(-1);
		}
	}
	s->a[s->top++] = x;
}

void STPop(ST* s)
{
	assert(s);
	assert(s->top > 0);
	s->top--;
}

STDataType STTop(ST* s)
{
	assert(s);
	assert(s->top > 0);
	return s->a[s->top - 1];
}

int STSize(ST* s)
{
	assert(s);
	return s->top;
}

bool STEmpty(ST* s)
{
	assert(s);
	return s->top == 0;
}

void STDestroy(ST* s)
{
	assert(s);
	free(s->a);
	s->a = NULL;
	s->top = s->capacity = 0;
}