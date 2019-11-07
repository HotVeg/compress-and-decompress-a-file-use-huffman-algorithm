#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "huffman.h"
#include "inout.h"

void PrintEnCode(int charsetFreq[], char charsetEncode[][CHAR_SET_SIZE])
{
	int i;
	for(i = 0; i < CHAR_SET_SIZE; i++)
	{
		if(*charsetEncode[i] != NULL)
			printf("[%c : %s]\n", i, charsetEncode[i]);
	}
}


int main(int argc, char *argv[])
{

/*
    Record the frequency of ASCII characters.
    Map ASCII character set to {0, 1, ..., CHAR_SET_SIZE - 1},
    which is the array subscript.
*/
    int charsetFreq[CHAR_SET_SIZE];
	char charsetEncode[CHAR_SET_SIZE][CHAR_SET_SIZE];
	HuffmanTree T = NULL;

    memset(charsetFreq, 0, sizeof(charsetFreq));
    memset(charsetEncode, 0, sizeof(charsetEncode));

    ReadData(argc, argv, charsetFreq, CHAR_SET_SIZE);
	PrintAll(charsetFreq, CHAR_SET_SIZE);
	T = BuildHuffmanTree(charsetFreq, CHAR_SET_SIZE);
	printf("The WPL is %ld\n", GetWPL(T));
	GetCharsetEnCode(T, charsetEncode, 0);
	 
	PrintEnCode(charsetFreq, charsetEncode);
	Compress(compressFilename, argv[1], charsetFreq, charsetEncode);


    return 0;
}

