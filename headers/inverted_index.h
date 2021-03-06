#ifndef INVERTED_INDEX_H_
#define INVERTED_INDEX_H_

#include <stdbool.h>

#define STRING_SIZE 21
#define PATH_SIZE 256
#define TMP_PATH_SIZE 16
#define MAX_FILES 16
#define II_SIZE 28

typedef struct inverted_index* IIndex;

IIndex new_ii();

void delete_ii( IIndex i );

void make_index( int *_n, long long int *_memSize, const char *_chats, const char *_index );

char* getKey ( IIndex i );

int* getFile  ( IIndex i );

int* getFreq  ( IIndex i );

int* getPos   ( IIndex i );

void setKey  ( IIndex i, char* key );

void setFile ( IIndex i, int file  );

void setFreq ( IIndex i, int freq  );

void setPos  ( IIndex i, int pos   );

bool compare( IIndex a, IIndex b );

#endif
