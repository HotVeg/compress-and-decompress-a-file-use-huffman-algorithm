#ifndef _INOUT_H
    #define _INOUT_H

#include "huffman.h"

void ReadData(int argc, char **argv, int charsetFreq[], int N);

void PrintAll(int charsetFreq[], int N);	// view character statistics

void WriteToFile(const char* dest, const char* src, int charsetFreq[], char charsetEncode[][CHAR_SET_SIZE]);

#endif//_INOUT_H