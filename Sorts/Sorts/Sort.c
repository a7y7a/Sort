#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"Stack.h"


void Swap(int* p1, int* p2)
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void insertSort(int* a, int n)
{
	int i = 0;
	for (i = 0; i < n - 1; i++)
	{
		int end = i;
		int tmp = a[end + 1];
		while (end >= 0)
		{
			if (a[end] > tmp)
			{
				a[end + 1] = a[end];
				end--;
			}
			else
			{
				break;
			}
		}
		a[end + 1] = tmp;
	}
}

void shellSort(int* a, int n)
{
	int i = 0;
	int gap = n;
	while (gap > 0)
	{
		gap /= 2;
		for (i = 0; i < n - gap; i++)
		{
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0)
			{
				if (a[end] > tmp)
				{
					a[end + gap] = a[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			a[end + gap] = tmp;
		}
	}
}

void selectSort(int* a, int n)
{
	int begin = 0;
	int end = n - 1;
	while (begin < end)
	{
		int i = 0;
		int max = begin, min = begin;
		for (i = begin; i <= end; i++)
		{
			if (a[i] > a[max])
			{
				max = i;
			}
			if (a[i] < a[min])
			{
				min = i;
			}
		}
		Swap(&a[begin], &a[min]);
		if (begin == max)
		{
			max = min;
		}
		Swap(&a[end], &a[max]);
		begin++;
		end--;
	}
}

void adjustDown(int* a, int n, int root)
{
	int parent = root;
	int child = parent * 2 + 1;
	while (child < n)
	{
		if (child + 1 < n && a[child] < a[child + 1])
		{
			child++;
		}
		if (a[parent] < a[child])
		{
			Swap(&a[parent], &a[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void heapSort(int* a, int n)
{
	int i = (n - 2) / 2;
	for (; i >= 0; i--)
	{
		adjustDown(a, n, i);
	}
	int end = n - 1;
	while (end)
	{
		Swap(&a[0], &a[end]);
		adjustDown(a, end, 0);
		end--;
	}
}

void bubbleSort(int* a, int n)
{
	int i = 0;
	for (; i < n - 1; i++)
	{
		int exchange = 0;
		int j = 0;
		for (; j < n - 1 - i; j++)
		{
			if (a[j] > a[j + 1])
			{
				Swap(&a[j], &a[j + 1]);
			}
			exchange = 1;
		}
		if (!exchange) return;
	}
}

int getMid(int* a, int left, int right)
{
	int mid = (left + right) / 2;
	if (a[left] < a[mid])
	{
		if (a[mid] < a[right])
		{
			return mid;
		}
		else if (a[left] > a[right])
		{
			return left;
		}
		else return right;
	}
	else
	{
		if (a[mid] > a[right])
		{
			return mid;
		}
		else if (a[left] < a[right])
		{
			return left;
		}
		else return right;
	}
}

//挖坑法
int partSort1(int* a, int left, int right)
{
	int mid = getMid(a, left, right);
	Swap(&a[left], &a[mid]);
	int begin = left, end = right;
	int pivot = begin, key = a[begin];
	while (begin < end)
	{
		while (begin < end && a[end] >= key)
		{
			end--;
		}
		a[pivot] = a[end];
		pivot = end;
		while (begin < end && a[begin] <= key)
		{
			begin++;
		}
		a[pivot] = a[begin];
		pivot = begin;
	}
	a[pivot] = key;
	return pivot;
}

//左右指针法
int partSort2(int* a, int left, int right)
{
	int mid = getMid(a, left, right);
	Swap(&a[left], &a[mid]);
	int begin = left, end = right;
	int key = begin;
	while (begin < end)
	{
		while (begin < end && a[end] >= a[key])
		{
			end--;
		}
		while (begin < end && a[begin] <= a[key])
		{
			begin++;
		}
		Swap(&a[begin], &a[end]);
	}
	Swap(&a[begin], &a[key]);
	return begin;
}

//前后指针法
int partSort3(int* a, int left, int right)
{
	int mid = getMid(a, left, right);
	Swap(&a[left], &a[mid]);
	int keyi = left;
	int cur = keyi + 1, prev = keyi;
	while (cur <= right)
	{
		if (a[cur] < a[keyi] && ++prev != cur)
		{
			Swap(&a[prev], &a[cur]);
		}
		cur++;
	}
	Swap(&a[prev], &a[keyi]);
	return prev;
}

void quickSort(int* a, int left, int right)
{
	if (left >= right) return;
	//int key = partSort1(a, left, right);
	//int key = partSort2(a, left, right);
	int key = partSort3(a, left, right);
	if (key - 1 - left > 10)
	{
		quickSort(a, left, key - 1);
	}
	else
	{
		insertSort(a, key - left);
	}
	if (right - (key + 1) > 10)
	{
		quickSort(a, key + 1, right);
	}
	else
	{
		insertSort(a + key + 1, right - key);
	}
}

void quickSortNR(int* a, int n)
{
	ST s;
	STInit(&s);
	STPush(&s, n - 1);
	STPush(&s, 0);
	while (!STEmpty(&s))
	{
		int left = STTop(&s);
		STPop(&s);
		int right = STTop(&s);
		STPop(&s);
		int key = partSort3(a, left, right);
		if (right > key + 1)
		{
			STPush(&s, right);
			STPush(&s, key + 1);
		}
		if (left < key - 1)
		{
			STPush(&s, key - 1);
			STPush(&s, left);
		}
	}
	STDestroy(&s);
}

void _mergeSort(int* a, int left, int right, int* tmp)
{
	if (left >= right) return;
	int mid = (left + right) >> 1;
	_mergeSort(a, left, mid, tmp);
	_mergeSort(a, mid + 1, right, tmp);
	int begin1 = left, end1 = mid, begin2 = mid + 1, end2 = right;
	int index = left;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (a[begin1] < a[begin2])
		{
			tmp[index++] = a[begin1++];
		}
		else
		{
			tmp[index++] = a[begin2++];
		}
	}
	while (begin1 <= end1)
	{
		tmp[index++] = a[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[index++] = a[begin2++];
	}
	int i = left;
	for (; i <= right; i++)
	{
		a[i] = tmp[i];
	}
}

void mergeSort(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	_mergeSort(a, 0 , n - 1, tmp);
	free(tmp);
}

void mergeSortNR(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	int gap = 1;
	while (gap < n)
	{
		int i = 0;
		for (; i < n; i += 2*gap)
		{
			int begin1 = i, end1 = i + gap - 1, begin2 = i + gap, end2 = i + 2 * gap - 1;
			if (end1 >= n) break;
			if (end2 >= n) end2 = n - 1;
			int index = i;
			while (begin1 <= end1 && begin2 <= end2)
			{
				if (a[begin1] < a[begin2])
				{
					tmp[index++] = a[begin1++];
				}
				else
				{
					tmp[index++] = a[begin2++];
				}
			}
			while (begin1 <= end1)
			{
				tmp[index++] = a[begin1++];
			}
			while (begin2 <= end2)
			{
				tmp[index++] = a[begin2++];
			}
		}
		int j = 0;
		for (; j < n; j++)
		{
			a[j] = tmp[j];
		}
		gap *= 2;
	}
	free(tmp);
}

void countSort(int* a, int n)
{
	int min = a[0], max = a[0];
	int i = 0;
	for (; i < n; i++)
	{
		if (a[i] < min)
		{
			min = a[i];
		}
		if (a[i] > max)
		{
			max = a[i];
		}
	}
	int range = max - min + 1;
	int* count = (int*)calloc(range, sizeof(int));
	for (i = 0; i < n; i++)
	{
		count[a[i] - min]++;
	}
	int j = 0;
	for (i = 0; i < range; i++)
	{
		while (count[i]--)
		{
			a[j++] = i + min;
		}
	}
}

void printArray(int* a, int n)
{
	int i = 0;
	for (i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

void insertTest()
{
	int a[8] = { 10, 6, 7 ,1, 3, 9, 4, 2 };
	int size = sizeof(a) / sizeof(a[0]);
	insertSort(a, size);
	printArray(a, size);
}

void shellTest()
{
	int a[8] = { 10, 6, 7 ,1, 3, 9, 4, 2 };
	int size = sizeof(a) / sizeof(a[0]);
	shellSort(a, size);
	printArray(a, size);
}

void selectTest()
{
	int a[8] = { 10, 6, 7 ,1, 3, 9, 4, 2 };
	int size = sizeof(a) / sizeof(a[0]);
	selectSort(a, size);
	printArray(a, size);
}

void heapTest()
{
	int a[8] = { 10, 6, 7 ,1, 3, 9, 4, 2 };
	int size = sizeof(a) / sizeof(a[0]);
	heapSort(a, size);
	printArray(a, size);
}

void bubbleTest()
{
	int a[8] = { 10, 6, 7 ,1, 3, 9, 4, 2 };
	int size = sizeof(a) / sizeof(a[0]);
	bubbleSort(a, size);
	printArray(a, size);
}

void quickTest()
{
	int a[8] = { 10, 6, 7 ,1, 3, 9, 4, 2 };
	int size = sizeof(a) / sizeof(a[0]);
	quickSort(a, 0, size - 1);
	printArray(a, size);
}

void quickNRTest()
{
	int a[8] = { 10, 6, 7 ,1, 3, 9, 4, 2 };
	int size = sizeof(a) / sizeof(a[0]);
	quickSortNR(a, size);
	printArray(a, size);
}

void mergeTest()
{
	int a[8] = { 10, 6, 7 ,1, 3, 9, 4, 2 };
	int size = sizeof(a) / sizeof(a[0]);
	mergeSort(a, size);
	printArray(a, size);
}

void mergeNRTest()
{
	//int a[8] = { 10, 6, 7 ,1, 3, 9, 4, 2 };
	int a[12] = { 10, 6, 7 ,1, 3, 9, 4, 2, 5, 8, 11, 12};
	int size = sizeof(a) / sizeof(a[0]);
	mergeSortNR(a, size);
	printArray(a, size);
}

void countTest()
{
	int a[8] = { 10, 6, 7 ,1, 3, 9, 4, 2 };
	int size = sizeof(a) / sizeof(a[0]);
	countSort(a, size);
	printArray(a, size);
}

void op()
{
	srand((unsigned int)time(NULL));
	int* a1 = (int*)malloc(sizeof(int) * 100000);
	int* a2 = (int*)malloc(sizeof(int) * 100000);
	int* a3 = (int*)malloc(sizeof(int) * 100000);
	int* a4 = (int*)malloc(sizeof(int) * 100000);
	int* a5 = (int*)malloc(sizeof(int) * 100000);
	int* a6 = (int*)malloc(sizeof(int) * 100000);
	int i = 0;
	for (i = 0; i < 100000; i++)
	{
		a6[i] = a5[i] = a4[i] = a3[i] = a2[i] = a1[i] = rand();
	}
	int begin1 = clock();
	insertSort(a1, 100000);
	int end1 = clock();
	int begin2 = clock();
	shellSort(a2, 100000);
	int end2 = clock();
	int begin3 = clock();
	selectSort(a3, 100000);
	int end3 = clock();
	int begin4 = clock();
	heapSort(a4, 100000);
	int end4 = clock();
	int begin5 = clock();
	bubbleSort(a5, 100000);
	int end5 = clock();	
	int begin6 = clock();
	quickSort(a6, 0, 100000 - 1);
	int end6 = clock();
	printf("insertSort:%d ", end1 - begin1);
	printf("shellSort:%d ", end2 - begin2);
	printf("selectSort:%d ", end3 - begin3);
	printf("heapSort:%d ", end4 - begin4);
	printf("bubbleSort:%d ", end5 - begin5);
	printf("quickSort:%d ", end6 - begin6);
	printf("\n");
	free(a1);
	free(a2);
	free(a3);
	free(a4);
	free(a5);
	free(a6);
}

int main()
{
	//op();
	countTest();
	return 0;
}