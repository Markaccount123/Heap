#include"Heap.h"

//����
void Swap(HPDateType* p1,HPDateType* p2)
{
	HPDateType tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}
//���µ����㷨
//ǰ�᣺������������С��
void AdjustDown(HPDateType* a, int n, int root)
{
	int parent = root;
	int child = parent * 2 + 1;//����
	while (child < n)
	{
		//�ҳ����Һ�����С����һ��
		//����һ����ȫ���������Һ��ӿ����ǲ����ڵģ�����child +1 �п����ǻ�Խ���
		if (child+1 < n  && a[child + 1] < a[child])
		{
			child++;
		}

		//�������С�ڸ����򽻻�
		if (a[child] < a[parent])
		{
			Swap(&a[child], &a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void HeapInit(Heap* php, HPDateType* a, int n)
{
	php->_a = (HPDateType)malloc(sizeof(HPDateType)*n);
	if (php->_a == NULL)
	{
		printf("�ڴ治��\n");
		exit(-1);
	}
	memcpy(php->_a, a, sizeof(HPDateType)*n); //����һ�����飬��һ������ϣ�����������������ֵ�������������ٵ����������
	php->_size = n;
	php->_capacity = n;
	//����Ŀǰ�����Ƕѣ���ֻ�ǰ�������������ݶ�������������

	//������
	//���ȱ�֤������������С�ѵ�����²��ܽ������µ����㷨�Ĳ���
	//����������е�������������ʱ��Ҫ�������濪ʼ���𣨵�������
	//��ÿһ�����Ƕ�������һ��С�ѣ����е���
	for (int i = (n - 1 - 1) / 2; i >= 0; --i)
	{
		AdjustDown(php->_a, php->_size, i);
	}

}

void AdjustUp(HPDateType* a, int n, int child)
{
	int parent = (child - 1) / 2;
	while (child > 0) //��Ϊ��child=0��ʱ�򣬴�ʱparent���Ѿ�С��0�ˣ��벻ͨ�Ļ����Լ�����������
	{
		if (a[child] < a[parent])
		{
			//���￼�ǵ������������������ȸ���ҪС��˵����ʱ�㲻�ܱ���С�ѵ��ص㣬��Ҫ����
			Swap(&a[child], &a[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}



void HeapDestory(Heap* php)
{
	assert(php);
	free(php->_a);
	php->_a = NULL;
	php->_size = php->_capacity = 0;
}

void HeapPush(Heap* php, HPDateType x)
{
	//����һ��Ҫ��̼�ס��ȫ�������Ķ��壬��Ҫ�����������������ݣ�Ӧ�����Ǹ�λ�ò���
	//�����������������������С�ѣ����������ڲ������һ�����ڸ��׵�����ô���ɱ�����С�ѵ��ص㣬����������������������һ��С�ڸ��׵���
	//��ʱ���С�ѵ��ص�Ͳ����ˣ���Ӧ����ô�죿����Ҫ�����ˣ�
	//������ص���ǽ���������±�����ʾ���ӹ�ϵ��
	//���Դ�ʱ������Ҫһ�����ϵ����㷨
	assert(php);
	//ֻҪ��˳���ļ������ݾ�Ҫ���ǵ��Ƿ���Ҫ����
	if (php->_size == php->_capacity)
	{
		php->_capacity *= 2;
		HPDateType* tmp = (HPDateType*)realloc(php->_a, sizeof(HPDateType)*php->_capacity);
		if (tmp == NULL)
		{
			printf("����ʧ��\n");
			exit(-1);
		}
		else
		{
			php->_a = tmp;
		}
	}
	php->_a[php->_size++] = x; //�����++�Ǻ��õģ��Ȼ�ʹ��php->_sizeȻ��ʹ������֮��Ż�++����Ϊ���size����Ч������Ҳ�ڲ��ϵ�����
	AdjustUp(php->_a, php->_size, php->_size - 1);
}

void HeapPop(Heap* php) //��Ϊֻ�иɵ��Ѷ��������С��ֵ������л����ҵ���С����
{
	//�����pop��Ŀ����ɾ�����Ѷ�������
	//��Ҫ����һ���ı��˶Ѷ������ݣ��ͻᷢ�������ṹ�ͻᷢ���ı䣬���ӹ�ϵʲô�Ķ�������
	assert(php);
	assert(php->_size > 0);// ������ﶼû���������㻹������ɾʲô


	Swap(php->_a[0], php->_a[php->_size - 1]);
	php->_size--;//���������Ҫ�ɵ��Ѷ��������
	AdjustDown(php->_a, php->_size, 0);

}

HPDateType HeapTop(Heap* php)
{
	//ȡ�Ѷ������ݣ�����0��λ��
	assert(php);
	assert(php->_size > 0);
	return php->_a[0];
}