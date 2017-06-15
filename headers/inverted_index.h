#ifndef INVERTED_INDEX_H_
#define INVERTED_INDEX_H_

#include <stdbool.h>

#define STRING_SIZE 21
#define PATH_SIZE 256
#define TMP_PATH_SIZE 16
#define MAX_FILES 16
#define II_SIZE 32

typedef struct inverted_index* InvertedIndex;

InvertedIndex new_ii( char* _key, int _file, int _freq, int _pos );

InvertedIndex new_empty();

void delete_ii( InvertedIndex i );

void make_index( int *_n, int *_memSize, const char *_chats, const char *_index );

char* getKey ( InvertedIndex i );

int getFile  ( InvertedIndex i );

int getFreq  ( InvertedIndex i );

int getPos   ( InvertedIndex i );

void setKey  ( InvertedIndex i, char* key );

void setFile ( InvertedIndex i, int file  );

void setFreq ( InvertedIndex i, int freq  );

void setPos  ( InvertedIndex i, int pos   );

bool compare( InvertedIndex a, InvertedIndex b );

#endif
