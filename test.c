#include"Heap.h"


void HeapSort(int* a, int n)
{
	//����
	//�������i=n-1��ʼ����Ҳ�������һ��λ�ÿ�ʼ������������ᷢ����Щ����Ҷ�ӣ��������ĺ��ӣ�������ѹ����û�к��ӣ�
	for (int i = (n - 1-1)/2; i >= 0; --i)
	{
		AdjustDown(a, n, i);
	}
	int end = n - 1; //end��������������Ԫ�ظ���
	while (end>0)
	{
		Swap(&a[0], &a[end]);
		//�ڼ���ѡ��С��
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