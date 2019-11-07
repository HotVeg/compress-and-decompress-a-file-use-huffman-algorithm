#ifndef _INOUT_H
    #define _INOUT_H

#include "huffman.h"


enum ASKFOR {OPEN_FILE, APPLY_MEMORY};

char compressFilename[200];

void ReadData(int argc, char **argv, int charsetFreq[], int N);

void PrintAll(int charsetFreq[], int N);	// view character statistics

void Compress(const char* dest, const char* src, int charsetFreq[], char charsetEncode[][CHAR_SET_SIZE]);

void Diagnose(const void * p, int type);

#endif//_INOUT_H