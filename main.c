#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "huffman.h"
#include "inout.h"

#define FILENAME_LEN 100
#define ENCODE_OPTION "-e"
#define DECODE_OPTION "-d"

char inputFile[FILENAME_LEN];
char outputFile[FILENAME_LEN];

void Help();

int main(int argc, char *argv[])
{
	if(argc < 3 || argc > 4)
	{
		printf("Huff: wrong input\n");
		Help();
		exit(0);
	}
	strcpy(inputFile, argv[2]);
	if(argc == 4)
		strcpy(outputFile, argv[3]);
	else
	{
		if(strcmp(argv[1], ENCODE_OPTION) == 0)
			strcat(strcpy(outputFile, argv[2]), EN_EXTENSION);
		else if(strcmp(argv[1], DECODE_OPTION) == 0)
			strcat(strcpy(outputFile, argv[2]), DE_EXTENSION);
		else
		{
			printf("Huff: invalid option -- \"%s\"\n", argv[1]);
			Help();
			exit(0);
		}
	}
	
	if(strcmp(argv[1], ENCODE_OPTION) == 0)
		EnCode(inputFile, outputFile);
	else if(strcmp(argv[1], DECODE_OPTION) == 0)
		DeCode(inputFile, outputFile);

    return 0;
}

void Help()
{
	printf("[Usage]: Huff [OPTION] ... [INPUT FILE] ... [OUTPUT FILE](optional)\n");
	printf("OPTION:\n");
	printf("-e\n");
	printf("	encode input file\n");
	printf("-d\n");
	printf("	decode input file\n");
}

