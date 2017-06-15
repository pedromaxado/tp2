#ifndef INVERTED_INDEX_H_
#define INVERTED_INDEX_H_

#include <stdbool.h>

#define STRING_SIZE 21
#define PATH_SIZE 256
#define MAX_FILES 16

typedef struct inverted_index* InvertedIndex;

bool compare( InvertedIndex a, InvertedIndex b );

void make_index( int _n, const int _memSize, const char* _chats, const char* _index );

#endif
