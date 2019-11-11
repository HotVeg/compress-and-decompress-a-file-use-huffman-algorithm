#ifndef _INOUT_H
    #define _INOUT_H

#include "huffman.h"


enum ASKFOR {OPEN_FILE, APPLY_MEMORY};

void EnCode(const char *inputFile, const char *outputFile);

void DeCode(const char *inputFile, const char *outputFile);

void ReadData(const char *inputFile, unsigned int freq[], int N);

void PrintAll(int charsetFreq[], int N);	// view character statistics

void Compress(const char* dest, const char* src, unsigned int charsetFreq[], char charsetEncode[][CHAR_SET_SIZE]);

void Diagnose(const void * p, int type);

#endif//_INOUT_H