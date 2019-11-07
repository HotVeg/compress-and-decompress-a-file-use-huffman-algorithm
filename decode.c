#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "inout.h"
#include "huffman.h"

char decompressFile[200];


int main(int argc, char **argv)
{
	HuffmanTree T;
    FILE * in, out;
	char cmpFile[100];
    int N;

    if(argc < 2)
    {
        printf("no input file\n");
        exit(0);
    }
    else if(argc == 3)
    {
        strcpy(decompressFile, argv[2]);
        strcat(decompressFile, DE_EXTENSION);
    }

    in = fopen(argv[1], "rb");
    Diagnose(in, OPEN_FILE);
	fread(&cmpFile, sizeof(FILE_IDENTIFIER), 1, in);
	if(strcmp(cmpFile, FILE_IDENTIFIER) != 0)
	{
		printf("File type mismatch\n");
		exit(-1);
	}
	DeInitCodeList(in);
	T = DeBuildHuffmanTree();
	//DeCompress();
    return 0;
}