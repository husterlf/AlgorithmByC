// mySort.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include<vector>
using namespace std;
//元素类型
typedef int ElementType;

class MySort {
public:
	MySort() {}
	~MySort() {}
	/*using part*/
	//插入排序
	void InsertionSort(ElementType A[],int N)
	{
		//从第下标1开始
		for (int i = 1; i < N; i++)
		{
			ElementType Tmp = A[i];
			int p;
			//*比较当前遍历元素，插入到之前的有序数组
			for (p = i; p>0&&A[p-1] > Tmp; p--)
				A[p] = A[p-1];

			A[p] = Tmp;

		}
	}
	//希尔排序
	void ShellSort(ElementType A[],int N)
	{
		//
		for (int Length = N / 2; Length > 0; Length /= 2)//序列为折半递减序列
		{
			for (int loc = Length; loc < 2*Length; loc++)
			{
				//插入排序
				for (int j = loc; j < N; j = j + Length)
				{
					ElementType Tmp = A[j];
					int i;
					//*i大于等于Length
					for (i = j; i >= Length && A[i- Length] > Tmp; i = i - Length)
						A[i] = A[i - Length];

					A[i] = Tmp;
				}
			}
		}

	}
	//堆排序
	void Heapsort(ElementType A[],int N)
	{
		//建堆,下沉N/2--0号元素即可完成，较大的元素浮上来
		for (int i = N/2; i >= 0; i--)
		{
			PercDown(A, i, N);
		}

		//下沉
		for (int j = N - 1; j >= 0; j--)
		{
			std::cout << A[0] << std::endl;
			mySwap(&A[j],&A[0]);
			PercDown(A, 0, j);
		}

	}
	//归并排序
	void Mergesort(ElementType A[],int N)
	{
		ElementType* TmpArray;
		TmpArray =(ElementType *)malloc(N*sizeof(ElementType));
		if (TmpArray != NULL)
		{
			MSort(A,TmpArray,0,N-1);
			free(TmpArray);
		}
		else
		{
			cout << "No space for tmp array!" << endl;
		}
	}
	//快速排序
	void Quicksort(ElementType A[], int N)
	{
		Qsort(A,0,N-1);
	}
	//快速选择，找到数组中第k个最小元素
	void Qselect(ElementType A[], int k,int Left,int Right)
	{
		int i, j;
		ElementType Pivot;
		//= Median3(A, Left, Right);
		if (Left + 3 <= Right)
		{
			Pivot = Median3(A, Left, Right);
			i = Left;
			j = Right - 1;
			for (;;)
			{
				while (A[++i] < Pivot) {}
				while (A[--j] > Pivot) {}
				if (i < j)
					mySwap(&A[i], &A[j]);
				else
					break;
			}

			mySwap(&A[i], &A[Right - 1]);
			if(k<=i)
				Qselect(A,k, Left, i - 1);
			else if(k>i+1)
				Qselect(A,k, i + 1, Right);
		}
		else
			InsertionSort(A + Left, Right - Left + 1);
	}

	void printVec(ElementType A[], int n)
	{
		for (int i = 0; i < n; i++)
			if (i != n - 1)
				cout << A[i] << ",";
			else
				cout << A[i];
	}

private:
	/*辅助函数*/
	void mySwap(ElementType *P1,ElementType *P2)
	{
		ElementType Tmp = *P1;
		*P1 = *P2;
		*P2 = Tmp;
	}


	//belongs to Heapsort
	void PercDown(ElementType A[],int i,int N)
	{
		//i号下标下沉大小为N的堆
		int Child;
		ElementType Tmp;
		for (Tmp = A[i];(2*i+1)<N;i=Child)
		{
			Child = (2 * i + 1);
			if (Child != N - 1 && A[Child + 1] > A[Child])
				Child++;
			if (Tmp < A[Child])
				A[i] = A[Child];
			else
				break;
		}
		A[i] = Tmp;
	}

	//belongs to Mergesort
	void MSort(ElementType A[],ElementType TmpArray[],int Left,int Right)
	{
		int Mid;
		if (Left < Right)
		{
			Mid = (Right + Left) / 2 ;
			MSort(A,TmpArray,Left,Mid);
			MSort(A, TmpArray, Mid+1, Right);
			Merge(A,TmpArray,Left,Mid+1,Right);
		}
	}

	void Merge(ElementType A[],ElementType TmpArray[],int Lpos,int Rpos,int RightEnd)
	{
		int i, LeftEnd, NumElements, TmpPos;
		LeftEnd = Rpos - 1;
		TmpPos = Lpos;
		NumElements = RightEnd - Lpos + 1;

		while (Lpos <= LeftEnd && Rpos <= RightEnd)
			if (A[Lpos] <= A[Rpos])
				TmpArray[TmpPos++] = A[Lpos++];
			else
				TmpArray[TmpPos++] = A[Rpos++];


		while (Lpos <= LeftEnd)
			TmpArray[TmpPos++] = A[Lpos++];
		while (Rpos <= RightEnd)
			TmpArray[TmpPos++] = A[Rpos++];

		for (i = 0; i < NumElements; i++, RightEnd--)
			A[RightEnd] = TmpArray[RightEnd];

	}

	//belongs to Quicksort
	ElementType Median3(ElementType A[],int Left,int Right)
	{
		int mid = (Left + Right) / 2;
		if (A[Left] > A[mid])
			mySwap(&A[Left],&A[mid]);
		if (A[Left] > A[Right])
			mySwap(&A[Left], &A[Right]);
		if (A[mid] > A[Right])
			mySwap(&A[Right], &A[mid]);

		mySwap(&A[mid],&A[Right-1]);

		return A[Right - 1];
	}

	void Qsort(ElementType A[],int Left,int Right)
	{
		int i, j;
		ElementType Pivot;
		//= Median3(A, Left, Right);
		if (Left + 3 <= Right)
		{
			Pivot = Median3(A,Left,Right);
			i = Left;
			j = Right - 1;
			for (;;)
			{
				while(A[++i]<Pivot){}
				while(A[--j]>Pivot){}
				if (i < j)
					mySwap(&A[i], &A[j]);
				else
					break;
			}

			mySwap(&A[i],&A[Right-1]);
			Qsort(A,Left,i-1);
			Qsort(A,i+1,Right);
		}
		else
			InsertionSort(A+Left,Right-Left+1);
	}


};



int main()
{
	ElementType A[20] = {3,12,98,119,-334,
		-22,-1,5,6,33,
		123,-9,44,1,5,
	-13,-22,35,53,39};
	int n = 20;

	MySort S;
	ElementType* p = A;
	//S.InsertionSort(p,n);
	//S.ShellSort(p,n);
	//S.Heapsort(p, n);
	//S.Mergesort(p, n);
	//S.Quicksort(p,n);
	//S.printVec(p, n);

	S.Qselect(p,4,0,n-1);

	cout <<A[2]<< A[3]<<A[4];

	//-334,-22,-22,-13,-9,-1,1,3,5,5,6,12,33,35,39,44,53,98,119,123
	//printVec(A,n);
	return -1;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
