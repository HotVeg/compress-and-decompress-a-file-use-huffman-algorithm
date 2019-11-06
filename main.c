#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "huffman.h"
#include "inout.h"

int main(int argc, char *argv[])
{

/*
    Record the frequency of ASCII characters.
    Map ASCII character set to {0, 1, ..., CHAR_SET_SIZE - 1},
    which is the array subscript.
*/
    int charsetFreq[CHAR_SET_SIZE];
	HuffmanTree T = NULL;
    memset(charsetFreq, 0, sizeof(charsetFreq));

    ReadData(argc, argv, charsetFreq, CHAR_SET_SIZE);
	PrintAll(charsetFreq, CHAR_SET_SIZE);
	T = BuildHuffmanTree(charsetFreq, CHAR_SET_SIZE);

    return 0;
}

