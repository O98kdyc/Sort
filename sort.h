#ifndef SORTING METHODS_H
#define SORTING METHODS_H
#include<iostream>
#include <string>
using namespace std;

struct node {
    int data;
    node *next;
    node() {next=NULL;}
    node(int d,node *n=NULL){data=d;next=n;}
};

void bubbleSort(int a[], int size);//冒泡排序
void quickSort(int a[], int low, int high);//快速排序
void quickSort(int a[], int size);
int divide( int a[], int low, int high);
void shellSort(int a[], int size); //希尔排序
void heapSort(int a[], int size); //堆排序
void percolateDown( int a[], int hole,int size);
void BucketSort(int a[],int size);
void bucketSort(node *&p);

//冒泡排序
void bubbleSort(int a[], int size)
{
    int i, j;
    int tmp;
    bool flag;      //记录一趟起泡中有没有发生过交换
    for (i = 1; i < size; ++i)
    {
        flag = false;
        for (j = 0; j < size-i; ++j)
        {
            if (a[j+1] < a[j])
            {
                tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;
                flag = true;
            }
        }
        if (!flag) break;
    }
}

//快速排序
void quickSort(int a[], int low, int high)
{
    int mid;
    if (low >= high) return;
    mid = divide(a, low, high);
    quickSort( a, low, mid-1);//排序左一半
    quickSort( a, mid+1, high);//排序右一半
}
void quickSort(int a[], int size)
{
    quickSort(a, 0, size-1);
}
int divide( int a[], int low, int high)
{
    int  k = a[low];
    do
    {
        while (low<high && a[high]>=k)
        {
            --high;
        }
        if (low < high)
        {
            a[low] = a[high];
            ++low;
        }
        while (low < high && a[low] <=k)
        {
            ++low;
        }
        if (low < high)
        {
            a[high] = a[low];
            --high;
        }
    }
    while (low != high);
    a[low] = k;
    return low;
}
//希尔排序
void shellSort(int a[], int size)
{
    int step, i, j;
    int tmp;
    for (step = size/2; step > 0; step /= 2)  //step为希尔增量
        for (i = step; i < size; ++i)
        {
            tmp = a[i];
            for (j = i - step; j >= 0 && a[j] > tmp;  j -= step)
                {a[j+step] = a[j];}
            a[j+step] = tmp;
        }
}
//堆排序
void heapSort(int a[], int size)
{
    int  i;
    int tmp;
// 创建初始的堆
    for(  i = size / 2 - 1; i >= 0; i-- )  percolateDown(a, i, size);

//执行n-1次deQueue
    for ( i = size - 1; i > 0; --i)
    {
        tmp = a[0];
        a[0] = a[i];
        a[i] = tmp;     //delete  a[0]
        percolateDown( a, 0, i );
    }
}
void percolateDown( int a[], int hole, int size )
{
    int child;
    int tmp = a[ hole ];
    for( ; hole * 2 + 1 < size; hole = child )
    {
        child = hole * 2 + 1;
        if( child != size - 1 && a[ child + 1 ] > a[ child ] )
            child++;
        if( a[ child ] > tmp )
        {
            a[ hole ] = a[ child ];
        }
        else  break;
    }
    a[ hole ] = tmp;
}

//希尔排序


void BucketSort(int a[],int size)
{
    node *head=new node(a[0]),*p;
    for(int i=1;i<size;i++) {head=new node(a[i],head);}
    bucketSort(head);
    for(int i=0;i<size;i++)
    {
        a[i]=head->data;
        p=head;
        head=head->next;
        delete p;
    }
}

void bucketSort(node *&p)                // p是链表头
{
    node *bucket[10], *last[10], *tail ;
    int i, j, k, base = 1, max = 0, len = 0;
    for (tail = p; tail != NULL; tail = tail->next)        // 找最大键值
	  if (tail->data > max) max = tail->data;

    // 寻找最大键值的位数
    if (max == 0) len = 0;
    else while (max > 0) { ++len; max /= 10; }
    for (i = 1; i <= len; ++i) {                 // 执行len次的分配与重组
       for (j = 0; j <= 9; ++j) bucket[j] = last[j] = NULL;
       while (p != NULL) {                                  // 执行一次分配
  	      k = p->data / base % 10;
	      if (bucket[k] == NULL)  bucket[k] = last[k] = p;
	      else last[k] = last[k]->next = p;
	      p = p->next;
      }
      p = NULL;                                             // 重组后的链表头
      for (j = 0; j <= 9; ++j) {                                  // 执行重组
 	     if (bucket[j] == NULL) continue;
	     if (p == NULL)  p = bucket[j];
	     else tail->next = bucket[j];
	     tail = last[j];
      }
      tail->next = NULL;                   // 表尾置空
      base *= 10;                          // 为下一次分配做准备
    }
}

#endif // SORTING METHODS_H
