#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <file_handler.h>
#include <internal_sort.h>
#include <external_sort.h>
#include <inverted_index.h>

struct inverted_index {
    char *key;
    int file,
        freq,
        pos;
};

InvertedIndex new_empty() {
    InvertedIndex i = ( InvertedIndex ) malloc( sizeof( struct inverted_index ) );

    i->key = ( char* ) malloc( STRING_SIZE * sizeof(char) );

    return i;
}

InvertedIndex new_ii( char* _key, int _file, int _freq, int _pos ) {
    InvertedIndex i = ( InvertedIndex ) malloc( sizeof( struct inverted_index ) );

    strcpy(i->key, _key);
    i->file = _file;
    i->freq = _freq;
    i->pos  = _pos;

    return i;
}

void delete_ii( InvertedIndex i ) {
    free(i->key);
    free(i);
}

char* getKey( InvertedIndex i ) {
    return i->key;
}

int getFile( InvertedIndex i ) {
    return i->file;
}

int getFreq( InvertedIndex i ) {
    return i->freq;
}

int getPos( InvertedIndex i ) {
    return i->pos;
}

void setFile( InvertedIndex i, int file ) {
    i->file = file;
}

void setFreq( InvertedIndex i, int freq ) {
    i->freq = freq;
}

void setPos( InvertedIndex i, int pos ) {
    i->pos = pos;
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

void make_index( int *_n, int *_memSize, const char* _chatsPaths, const char* _indexPath ) {

    int fileCount = sort_chats( _n, _memSize, _chatsPaths );

    merge_files( fileCount );

    FILE* indexFile;

    char* indexFilePath = ( char* ) malloc( PATH_SIZE * sizeof( char ) );

    sprintf(indexFilePath, "%sindex", _indexPath);

    indexFile = open_file(indexFilePath, "w");

    close_file(indexFile);
    free(indexFilePath);
}
