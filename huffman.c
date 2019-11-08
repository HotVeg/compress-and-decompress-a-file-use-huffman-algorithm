#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"
#include "minHeap.h"
#include "inout.h"




long GetWPL2(HuffmanTree T, int depth);

void AddToDecodeTree(HuffmanTree T, char ch, FILE * out);


struct _HNode * MakeHuffmanNode(int weight, char data)
{
	struct _HNode* s = (struct _HNode*)malloc(sizeof(struct _HNode));
	s->weight = weight;
	s->data = data;
	s->left = s->right = NULL;
	
	return s;
}

int CmpHuffmanNode(HuffmanTree T1, HuffmanTree T2)
{
	return T1->weight - T2->weight;
}

// Built with minimal heap
HuffmanTree BuildHuffmanTree(int charsetFreq[], int N)
{
    MinHeap H = BuildMinHeap(charsetFreq, N);
    HuffmanTree T = NULL, T1 = NULL, T2 = NULL;

    while(GetSize(H) > 1)
    {
        T1 = DeleteMin(H);
        T2 = DeleteMin(H);
        T = MakeHuffmanNode(T1->weight + T2->weight, '0');
        T->left = T1;
        T->right = T2;
        Insert(H, T);
    }
    T = DeleteMin(H);

    free(H);
    return T;
}

long GetWPL(HuffmanTree T)
{
	return GetWPL2(T, 0);
}

long GetWPL2(HuffmanTree T, int depth)
{
	if(T->left == NULL && T->right == NULL)
		return T->weight * depth;
	return GetWPL2(T->left, depth + 1) + GetWPL2(T->right, depth + 1);
	
}

void GetCharsetEnCode(HuffmanTree T, char charsetEncode[][CHAR_SET_SIZE], int depth)
{
	static char encode[CHAR_SET_SIZE];

	if(!T)
		return;
	if(T->left == NULL && T->right == NULL)
	{
		encode[depth] = '\0';
		strcpy(charsetEncode[T->data], encode);
	}
	if(T->left)
	{
		encode[depth] = '0';
		GetCharsetEnCode(T->left, charsetEncode, depth+1);
	}
	if(T->right)
	{
		encode[depth] = '1';	// backtracking
		GetCharsetEnCode(T->right, charsetEncode, depth+1);
	}
}

void DeInitCodeList(FILE* in)
{
	int N, i;

    fread(&N, sizeof(int), 1, in);
	printf("Detected %d dirrerent characters\n", N);
	codeList.codenodes = (CodeNode*)malloc(sizeof(CodeNode) * N);
	Diagnose(codeList.codenodes, APPLY_MEMORY);
	codeList.capacity = N;
	codeList.size = N;

	fread(codeList.codenodes, sizeof(CodeNode), N, in);
	printf("Detected the fllowing code table\n");
	for(i = 0; i < codeList.size; i++)
		printf("[%c : %s]\n", codeList.codenodes[i].data, codeList.codenodes[i].codeword);
}

HuffmanTree DeBuildHuffmanTree()
{
	HuffmanTree T, S;
	int i;
	char* pch;

	T = MakeHuffmanNode(0, 0);
	S = T;
	for(i = 0; i < codeList.size; i++)
	{
		for(pch = codeList.codenodes[i].codeword; *pch != '\0'; pch++)
		{
			if(*pch == '0')
			{
				if(!S->left)
					S->left = MakeHuffmanNode(0, 0);
				 S = S->left;
			}
			else
			{
				if(!S->right)
					S->right = MakeHuffmanNode(0, 0);
				 S = S->right;
			}
		}
		if(S->left || S->right)
			printf("error debuid-codetree\n");
		// arrived a leave
		S->data = codeList.codenodes[i].data;
		
		S = T;
	}
	return T;
}

void DeCompress(HuffmanTree T, FILE * in, FILE * out)
{
	int paddingBits;
	long start, end;
	char ch;

	fread(&paddingBits, sizeof(int), 1, in);
	printf("the paddingBits = %d\n", paddingBits);
	start = ftell(in);
	fseek(in, -1L, SEEK_END);
	end = ftell(in);
	fseek(in, start - end, SEEK_CUR);
	while(start < end)
	{
		fread(&ch, sizeof(ch), 1, in);
		AddToDecodeTree(T, ch, 8, out);

		start++;
	}
	fread(&ch, sizeof(ch), 1, in);
	AddToDecodeTree(T, ch, 8 - paddingBits, out);
}

void AddToDecodeTree(HuffmanTree T, char ch, int validBits, FILE * out)
{
	static HuffmanTree S = NULL;
	static int flag = 1;
	char mask;
	int i;
	
	if(flag)
	{
		S = T;
		flag = 0;
	}

	if(!T->left && ! T->right)
	{
		printf("error tree\n");
		return;
	}
	for(i = 1; i <= validBits; i++)
	{
		mask = 1;
		mask <<= (8 - i);
		if((ch & mask) == mask)
		{
			S = S->right;
		}
		else
		{
			S = S->left;
		}

		if(!S->left && !S->right)
		{
			fwrite(&(S->data), sizeof(S->data), 1, out);
			S = T;
		}
	}
}
