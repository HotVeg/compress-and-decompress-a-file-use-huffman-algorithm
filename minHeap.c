#include <stdlib.h>
#include <stdio.h>

#include "minHeap.h"
#include "huffman.h"


struct _HeapNode{
    ElemType *elems;
    int size;
    int capacity;
};


MinHeap BuildMinHeap(int charsetFreq[], int N)
{
    MinHeap H = NULL;
    HuffmanTree T = NULL;
    int i;

    H = (MinHeap)malloc(sizeof(struct _HeapNode));
    if(H == NULL)
    {
        printf("malloc heapnode failed\n");
        exit(-1);
    }
	H->capacity = N;
	H->size = 0;
    H->elems = (ElemType*)malloc(sizeof(ElemType) * (N + 1));
    if(H->elems == NULL)
    {
        printf("malloc heap failed\n");
        exit(-1);
    }

    for(i = 0; i < N; i++)
    {
        if(charsetFreq[i] > 0)
        {
            T = MakeHuffmanNode(charsetFreq[i], i);
            Insert(H, T);
        }
    }

    return H;
}

ElemType DeleteMin(MinHeap H)
{
    ElemType temp;
    if(Empty(H))
    {
        printf("DeleteMin error\n");
        return NULL;
    }
    else
    {
        temp = H->elems[1];
        H->elems[1] = H->elems[H->size--];
        AdjustDown(H, 1);

        return temp;
    }
}

void Insert(MinHeap H, ElemType T)
{
    if(Full(H))
    {
        printf("Insert error\n");
        exit(-1);
    }
    else
    {
        H->elems[++H->size] = T;
        AdjustUp(H, H->size);
    }   
}

void AdjustDown(MinHeap H, int p)
{
    int child;
    ElemType temp = H->elems[p];
    for(; 2 * p <= H->size; p = child)
    {
        child = 2 * p;
        if(child < H->size && CmpHuffmanNode(H->elems[child+1], H->elems[child]) < 0)
            child++;
		if(CmpHuffmanNode(H->elems[child], temp) < 0)
            H->elems[p] = H->elems[child];
        else
        {
            break;
        }
    }
    H->elems[p] = temp;
}

void AdjustUp(MinHeap H, int p)
{
    ElemType temp = H->elems[p];
    while(p > 1 && CmpHuffmanNode(temp, H->elems[p/2]) < 0)
    {
        H->elems[p] = H->elems[p/2];
        p /= 2;
    }
    H->elems[p] = temp;
}

int Empty(MinHeap H)
{
    return H->size == 0;
}

int Full(MinHeap H)
{
    return H->size == H->capacity;
}

int GetSize(MinHeap H)
{
	return H->size;
}

