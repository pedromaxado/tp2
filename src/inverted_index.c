#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <external_sort.h>
#include <inverted_index.h>
#include <file_handler.h>

#define TMP_PATH "./tmp/"
#define AUX_INDEX_PATH "./tmp/aux_index"
#define II_SIZE sizeof(struct inverted_index)

struct inverted_index {
    char *key;
    int file,
        freq,
        pos;
};

struct buffer {
    InvertedIndex* buf;
    size_t size;
};

InvertedIndex new_InvertedIndex( char* _key, int _file, int _freq, int _pos ) {
    InvertedIndex i = ( InvertedIndex ) malloc( sizeof( struct inverted_index ) );

    strcpy(i->key, _key);
    i->file = _file;
    i->freq = _freq;
    i->pos  = _pos;

    return i;
}

void delete_InvertedIndex( InvertedIndex i ) {
    free(i->key);
    free(i);
}

bool compare( InvertedIndex a, InvertedIndex b ) {

    if ( strcmp(a->key, b->key) < 0 ) {
        return true;
    }
    else if ( strcmp(a->key, b->key) > 0 ) {
        return false;
    }
    else {
        if ( a->file < b->file ) {
            return true;
        }
        else if ( a->file > b->file ) {
            return false;
        }
        else {
            if ( a->pos < b->pos  ) {
                return true;
            }
            else {
                return false;
            }
        }
    }
}

void write_partial_ii( FILE* fp, InvertedIndex i ) {
    fprintf(fp, "%s %d %d\n", i->key, i->file, i->pos);
}

void sort_chats( int _n, int _memSize, const char* _chatsPaths ) {

    FILE *chatFile, *outputs;
    char *chatPath, *outPath, *chatFileNumb, *word;
    int chunkSize, memCount, i;

    InvertedIndex* iiArray;

    chunkSize = _memSize / II_SIZE;

    chatFileNumb = ( char* ) malloc( MAX_FILES * sizeof(char) );
    chatPath = ( char* ) malloc( PATH_SIZE * sizeof(char) );

    word = ( char* ) malloc( STRING_SIZE * sizeof(char) );

    chatPath[0] = '\0';

    for ( i = 0; i < _n; i++ ) {
        sprintf( chatFileNumb, "%d", i );

        strcat ( chatPath, _chatsPaths  );
        strcat ( chatPath, chatFileNumb );

        chatFile = open_file(chatPath, "r");

        memCount = 0;

        while ( fscanf(chatFile, "%s", word) != EOF && memCount <= chunkSize ) {

        }
    }
}

void make_index( int _n, const int _memSize, const char* _chatsPaths, const char* _indexPath ) {

    sort_chats( _n, _memSize, _chatsPaths );
}
