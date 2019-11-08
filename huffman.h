#ifndef _HUFFMAN_H
    #define _HUFFMAN_H

#include <stdio.h>

#define CHAR_SET_SIZE 256
#define FILE_IDENTIFIER "huffman"
#define EN_EXTENSION ".huff"
#define DE_EXTENSION ".de_huff"

typedef struct _CodeNode CodeNode;

struct _CodeNode{
    char data;
    char codeword[CHAR_SET_SIZE];
};

struct _CodeTable{
    CodeNode* codenodes;
    int size;
    int capacity;
}codeList;

typedef struct _HNode * HuffmanTree;
struct _HNode{
    char data;
    int weight;
    struct _HNode *left;
    struct _HNode *right; 
};

int CmpHuffmanNode(HuffmanTree T1, HuffmanTree T2);

struct _HNode * MakeHuffmanNode(int weight, char data);

HuffmanTree BuildHuffmanTree(int charsetFreq[], int N);

long GetWPL(HuffmanTree T);

void GetCharsetEnCode(HuffmanTree T, char charsetEncode[][CHAR_SET_SIZE], int depth);

void DeInitCodeList(FILE* in);

HuffmanTree DeBuildHuffmanTree();

void DeCompress(HuffmanTree T, FILE * in, FILE * out);

#endif //_HUFFMAN_H