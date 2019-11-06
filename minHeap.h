#ifndef _MIN_HEAP_H
    #define _MIN_HEAP_H

#include "huffman.h"


typedef HuffmanTree ElemType;

typedef struct _HeapNode *MinHeap;

MinHeap BuildMinHeap(int charsetFreq[], int N);

struct _HNode * MakeNewHNode(int weight, char data);

ElemType DeleteMin(MinHeap H);

void Insert(MinHeap H, ElemType T);

void AdjustDown(MinHeap H, int p);

void AdjustUp(MinHeap H, int p);

int Empty(MinHeap H);

int Full(MinHeap H);

int GetSize(MinHeap H);

#endif //_MIN_HEAP_H