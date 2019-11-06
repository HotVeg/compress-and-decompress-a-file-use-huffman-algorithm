#include <malloc.h>
#include <stdlib.h>
#include "huffman.h"
#include "minHeap.h"


// Built with minimal heap
HuffmanTree BuildHuffmanTree(int charsetFreq[], int N)
{
    MinHeap H = BuildMinHeap(charsetFreq, N);
    HuffmanTree T = NULL, T1 = NULL, T2 = NULL;

    while(GetSize(H) > 1)
    {
        T1 = DeleteMin(H);
        T2 = DeleteMin(H);
        T1->left = T2;
        T = MakeNewHNode(T1->weight + T2->weight, '0');
        T->left = T1;
        T->right = T2;
        Insert(H, T);
    }
    T = DeleteMin(H);

    free(H);
    return T;
}


