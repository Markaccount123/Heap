#pragma once
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>
typedef int HPDateType;


//Ð¡¶Ñ
typedef struct Heap
{
	HPDateType* _a;
	int _size;
	int _capacity;
}Heap;


void AdjustDown(HPDateType* a, int n, int root);

void AdjustUp(HPDateType* a, int n, int child);

void HeapInit(Heap* php, HPDateType* a, int n);

void HeapDestory(Heap* php);

void HeapPush(Heap* php, HPDateType x);

void HeapPop(Heap* php);

HPDateType HeapTop(Heap* php);