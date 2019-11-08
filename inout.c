#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inout.h"


int paddingBits;

void WriteFileHeader(int charsetFreq[], char charsetEncode[][CHAR_SET_SIZE], FILE * out );

void WriteContent(FILE* in, FILE* out, char charsetEncode[][CHAR_SET_SIZE]);

void WriteCodeWord(const char* codes, FILE* out);

void WriteBit(char ch, FILE* out);


void ReadData(int argc, char **argv, int charsetFreq[], int N)
{
    FILE *in;
    char ch;
    if(argc < 2)
    {
        printf("no input file\n");
		printf("[Usage: ./encode file]");
        exit(-1);
    }
	else if(argc == 3)
	{
		strcpy(compressFilename, argv[2]);
		strcat(compressFilename, EN_EXTENSION);
	}
	else
	{
		strcpy(compressFilename, "encode");
		strcat(compressFilename, EN_EXTENSION);
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

void Compress(const char* dest, const char* src, int charsetFreq[], char charsetEncode[][CHAR_SET_SIZE])
{
	FILE* in  = NULL, *out = NULL;
	in = fopen(src, "r");
	if(in == NULL)
	{
		printf("open \"%s\" failed\n", src);
		exit(-1);
	}
	out = fopen(dest, "wb");
	if(out == NULL)
	{
		printf("open \"%s\" failed\n", dest);
		exit(-1);
	}

	WriteFileHeader(charsetFreq, charsetEncode, out);
	WriteContent(in, out, charsetEncode);

	fclose(in);
	fclose(out);
}


/*
*	FileHeader structure��
*	N: |charset|
*	record_1: char data + char codeword[256]
*	record_2
*	...
*	record_N
*	paddingBits
*/
void WriteFileHeader(int charsetFreq[], char charsetEncode[][CHAR_SET_SIZE], FILE * out )
{
	CodeNode record;

	int charsetNum, i, temp;

	charsetNum = 0; temp = 0;
	for(i = 0; i < CHAR_SET_SIZE; i++)
	{
		if(charsetFreq[i] > 0)
		{
			charsetNum++;
			temp += strlen(charsetEncode[i]) * charsetFreq[i];
			temp = temp % 8;
		}
	}
	paddingBits = (8 - temp) % 8;

	fwrite(FILE_IDENTIFIER, sizeof(FILE_IDENTIFIER), 1, out);
	fwrite(&charsetNum, sizeof(charsetNum), 1, out);

	for(i = 0; i < CHAR_SET_SIZE; i++)
	{
		if(charsetFreq[i] > 0)
		{
			record.data = (char)i;
			strcpy(record.codeword, charsetEncode[i]);
			fwrite(&record, sizeof(record), 1, out);
		}
	}
	fwrite(&paddingBits, sizeof(paddingBits), 1, out);
}

void WriteContent(FILE* in, FILE* out, char charsetEncode[][CHAR_SET_SIZE])
{
	int i;
	char ch;
	char* p;
	while( (ch = fgetc(in)) != EOF)
	{
		WriteCodeWord(charsetEncode[ch], out);
	}

	for(i = 0; i < paddingBits; i++)
		WriteBit('0', out);
}

void WriteCodeWord(const char* codes, FILE* out)
{
	const char * p = codes;
	while( *p != '\0' )
	{
		WriteBit(*p, out);
		p++;
	}
}

void WriteBit(char ch, FILE* out)
{
	static char buffer = 0;
	static int cnt = 0;
	char temp;
	if(ch == '1')
	{
		temp = 1;
		buffer |= (temp << (7-cnt));
	}
	cnt++;
	if(cnt == 8)
	{
		fwrite(&buffer, sizeof(buffer), 1, out);
		cnt = 0;
		buffer = 0;
	}
}

void Diagnose(const void * p, int type)
{
	if(p == NULL)
	{
		if(type == OPEN_FILE)
		{
			printf("open file failed\n");
		}
		else if(type == APPLY_MEMORY)
		{
			printf("apply memory failed\n");
		}
		exit(-1);
	}
}
