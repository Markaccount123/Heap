#include"Heap.h"


void HeapSort(int* a, int n)
{
	//建堆
	//这里可以i=n-1开始调，也就是最后一个位置开始调整，但是你会发现那些都是叶子，你算他的孩子（但是它压根就没有孩子）
	for (int i = (n - 1-1)/2; i >= 0; --i)
	{
		AdjustDown(a, n, i);
	}
	int end = n - 1; //end代表的数组里面的元素个数
	while (end>0)
	{
		Swap(&a[0], &a[end]);
		//在继续选次小的
		AdjustDown(a, end, 0);
		end--;
	}
}
int main()
{
	int a[] = { 27, 15, 19, 18, 28, 34, 65, 49, 25, 37 };
	HeapSort(a, sizeof(a) / sizeof(HPDateType));
	/*Heap hp;
	HeapInit(&hp, a, sizeof(a) / sizeof(HPDateType));*/
	return 0;
}