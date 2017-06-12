#ifndef INVERTED_INDEX_H_
#define INVERTED_INDEX_H_

#define STRING_SIZE 20
#define PATH_SIZE 256
#define MAX_FILES 16

#define TMP_PATH "./tmp/"

typedef struct inverted_index* InvertedIndex;

void make_index( int _n, const char* _chats, const char* _index );

#endif
