#ifndef _HUFFMAN_H
    #define _HUFFMAN_H

#define CHAR_SET_SIZE 256

typedef struct _HNode * HuffmanTree;
// minHeap.c模块需要使用此结构体，故在此文件中直接将定义暴露出来
struct _HNode{
    char data;
    int weight;
    struct _HNode *left;
    struct _HNode *right; 
};

HuffmanTree BuildHuffmanTree(int charsetFreq[], int N);

#endif //_HUFFMAN_H