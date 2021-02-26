#include"Heap.h"

//交换
void Swap(HPDateType* p1,HPDateType* p2)
{
	HPDateType tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}
//向下调整算法
//前提：左右子树都是小堆
void AdjustDown(HPDateType* a, int n, int root)
{
	int parent = root;
	int child = parent * 2 + 1;//左孩子
	while (child < n)
	{
		//找出左右孩子中小的那一个
		//这是一个完全二叉树，右孩子可能是不存在的，所以child +1 有可能是会越界的
		if (child+1 < n  && a[child + 1] < a[child])
		{
			child++;
		}

		//如果孩子小于父亲则交换
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
		printf("内存不足\n");
		exit(-1);
	}
	memcpy(php->_a, a, sizeof(HPDateType)*n); //我有一个数组，我一上来就希望你把这个数组里面的值都放在你所开辟的这个堆里面
	php->_size = n;
	php->_capacity = n;
	//但是目前还不是堆，你只是把数组里面的内容都放在了这里面

	//构建堆
	//首先保证左右子树都是小堆的情况下才能进行向下调整算法的操作
	//但是这里进行调整左右子树的时候要从最下面开始调起（倒着来）
	//把每一个三角都看作是一个小堆，进行调整
	for (int i = (n - 1 - 1) / 2; i >= 0; --i)
	{
		AdjustDown(php->_a, php->_size, i);
	}

}

void AdjustUp(HPDateType* a, int n, int child)
{
	int parent = (child - 1) / 2;
	while (child > 0) //因为当child=0的时候，此时parent早已经小于0了，想不通的话，自己画个堆来看
	{
		if (a[child] < a[parent])
		{
			//这里考虑的是如果你插入的这个数比父亲要小，说明此时你不能保持小堆的特点，需要交换
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
	//这里一定要深刻记住完全二叉树的定义，你要往这个堆里面插入数据，应该在那个位置插入
	//本来你这里的左右子树都是小堆，但是你现在插入的是一个大于父亲的数那么依旧保持着小堆的特点，但是你在这里如果插入的是一个小于父亲的数
	//此时你的小堆的特点就不对了，你应该怎么办？（需要处理了）
	//堆这个特点就是借助数组的下标来表示父子关系的
	//所以此时这里需要一个向上调整算法
	assert(php);
	//只要是顺序表的加入数据就要考虑到是否需要增容
	if (php->_size == php->_capacity)
	{
		php->_capacity *= 2;
		HPDateType* tmp = (HPDateType*)realloc(php->_a, sizeof(HPDateType)*php->_capacity);
		if (tmp == NULL)
		{
			printf("开辟失败\n");
			exit(-1);
		}
		else
		{
			php->_a = tmp;
		}
	}
	php->_a[php->_size++] = x; //这里的++是后置的，先会使用php->_size然后使用完了之后才会++，因为你的size是有效的数据也在不断的增加
	AdjustUp(php->_a, php->_size, php->_size - 1);
}

void HeapPop(Heap* php) //因为只有干掉堆顶的这个最小的值，你才有机会找到次小的数
{
	//这里的pop的目的是删除掉堆顶的数据
	//你要明白一旦改变了堆顶的数据，就会发现整个结构就会发生改变，父子关系什么的都会重新
	assert(php);
	assert(php->_size > 0);// 如果这里都没有数据了你还在那里删什么


	Swap(php->_a[0], php->_a[php->_size - 1]);
	php->_size--;//这里是真的要干掉堆顶这个数据
	AdjustDown(php->_a, php->_size, 0);

}

HPDateType HeapTop(Heap* php)
{
	//取堆顶的数据，就是0的位置
	assert(php);
	assert(php->_size > 0);
	return php->_a[0];
}