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
    unsigned char data;
    int weight;
    struct _HNode *left;
    struct _HNode *right; 
};

void EnCode(const char *inputFile, const char *outputFile);

void DeCode(const char *inputFile, const char *outputFile);

int CmpHuffmanNode(HuffmanTree T1, HuffmanTree T2);

struct _HNode * MakeHuffmanNode(int weight, unsigned char data);

HuffmanTree BuildHuffmanTree(unsigned int charsetFreq[], int N);

void DeInitCodeList(FILE* in);

HuffmanTree DeBuildHuffmanTree();

void DeCompress(HuffmanTree T, FILE * in, FILE * out);

#endif //_HUFFMAN_H