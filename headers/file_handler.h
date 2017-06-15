#ifndef FILE_HANDLER_H_
#define FILE_HANDLER_H_

#include <stdio.h>
#include <inverted_index.h>

FILE* open_file( char* path, char* mode );

void close_file( FILE* fp );

void write_ii( FILE* fp, InvertedIndex i );

void write_partial_ii( FILE* fp, InvertedIndex i );

#endif
