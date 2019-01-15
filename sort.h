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

void bubbleSort(int a[], int size);//ð������
void quickSort(int a[], int low, int high);//��������
void quickSort(int a[], int size);
int divide( int a[], int low, int high);
void shellSort(int a[], int size); //ϣ������
void heapSort(int a[], int size); //������
void percolateDown( int a[], int hole,int size);
void BucketSort(int a[],int size);
void bucketSort(node *&p);

//ð������
void bubbleSort(int a[], int size)
{
    int i, j;
    int tmp;
    bool flag;      //��¼һ����������û�з���������
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

//��������
void quickSort(int a[], int low, int high)
{
    int mid;
    if (low >= high) return;
    mid = divide(a, low, high);
    quickSort( a, low, mid-1);//������һ��
    quickSort( a, mid+1, high);//������һ��
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
//ϣ������
void shellSort(int a[], int size)
{
    int step, i, j;
    int tmp;
    for (step = size/2; step > 0; step /= 2)  //stepΪϣ������
        for (i = step; i < size; ++i)
        {
            tmp = a[i];
            for (j = i - step; j >= 0 && a[j] > tmp;  j -= step)
                {a[j+step] = a[j];}
            a[j+step] = tmp;
        }
}
//������
void heapSort(int a[], int size)
{
    int  i;
    int tmp;
// ������ʼ�Ķ�
    for(  i = size / 2 - 1; i >= 0; i-- )  percolateDown(a, i, size);

//ִ��n-1��deQueue
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

//ϣ������


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

void bucketSort(node *&p)                // p������ͷ
{
    node *bucket[10], *last[10], *tail ;
    int i, j, k, base = 1, max = 0, len = 0;
    for (tail = p; tail != NULL; tail = tail->next)        // ������ֵ
	  if (tail->data > max) max = tail->data;

    // Ѱ������ֵ��λ��
    if (max == 0) len = 0;
    else while (max > 0) { ++len; max /= 10; }
    for (i = 1; i <= len; ++i) {                 // ִ��len�εķ���������
       for (j = 0; j <= 9; ++j) bucket[j] = last[j] = NULL;
       while (p != NULL) {                                  // ִ��һ�η���
  	      k = p->data / base % 10;
	      if (bucket[k] == NULL)  bucket[k] = last[k] = p;
	      else last[k] = last[k]->next = p;
	      p = p->next;
      }
      p = NULL;                                             // ����������ͷ
      for (j = 0; j <= 9; ++j) {                                  // ִ������
 	     if (bucket[j] == NULL) continue;
	     if (p == NULL)  p = bucket[j];
	     else tail->next = bucket[j];
	     tail = last[j];
      }
      tail->next = NULL;                   // ��β�ÿ�
      base *= 10;                          // Ϊ��һ�η�����׼��
    }
}

#endif // SORTING METHODS_H
