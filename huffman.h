#ifndef _HUFFMAN_H
    #define _HUFFMAN_H

#define CHAR_SET_SIZE 256

typedef struct _HNode * HuffmanTree;

int CmpHuffmanNode(HuffmanTree T1, HuffmanTree T2);

struct _HNode * MakeHuffmanNode(int weight, char data);

HuffmanTree BuildHuffmanTree(int charsetFreq[], int N);

long GetWPL(HuffmanTree T);

void GetCharsetEnCode(HuffmanTree T, char charsetEncode[][CHAR_SET_SIZE], int depth);


#endif //_HUFFMAN_H