#include <stdio.h>
#include <stdlib.h>
#include "inout.h"


void ReadData(int argc, char **argv, int charsetFreq[], int N)
{
    FILE *in;
    char ch;
    if(argc < 2)
    {
        printf("no input file\n");
        exit(-1);
    }
    in = fopen(argv[1], "r");
    if(in == NULL)
    {
        printf("open file \"%s\" failed!\n", argv[1]);
        exit(-1);
    }
    ch = fgetc(in);
    while(ch != EOF)
    {
        charsetFreq[ch]++;
		ch = fgetc(in);
    }

    fclose(in);
}

void PrintAll(int charsetFreq[], int N)
{
	int i, cnt;
	for(i = 0, cnt = 0; i < N; i++)
    {
        if(charsetFreq[i] == 0)
            continue;

        if(i == '\t')
            printf("[\\t: %8d]  ", charsetFreq[i]);
        else if(i == '\n')
            printf("[\\n: %8d]  ", charsetFreq[i]);
        else
            printf("[%c : %8d]  ", i, charsetFreq[i]);
        if(++cnt % 4 == 0)
            putchar('\n');
    }
	putchar('\n');
}