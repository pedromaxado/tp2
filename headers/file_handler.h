#ifndef FILE_HANDLER_H_
#define FILE_HANDLER_H_

#include <stdio.h>

FILE* open_file( char* path, char* mode );

void close_file( FILE* fp );

#endif
