#ifndef _HUFFMAN_H
    #define _HUFFMAN_H

#define CHAR_SET_SIZE 256

typedef struct _HNode * HuffmanTree;
// minHeap.cģ����Ҫʹ�ô˽ṹ�壬���ڴ��ļ���ֱ�ӽ����屩¶����
struct _HNode{
    char data;
    int weight;
    struct _HNode *left;
    struct _HNode *right; 
};

HuffmanTree BuildHuffmanTree(int charsetFreq[], int N);

#endif //_HUFFMAN_H