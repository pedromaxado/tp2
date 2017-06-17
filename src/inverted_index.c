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

IIndex new_empty() {
    IIndex i = ( IIndex ) malloc( sizeof( struct inverted_index ) );

    i->key = ( char* ) malloc( STRING_SIZE * sizeof(char) );

    return i;
}

IIndex new_ii( char* _key, int _file, int _freq, int _pos ) {
    IIndex i = ( IIndex ) malloc( sizeof( struct inverted_index ) );

    strcpy(i->key, _key);
    i->file = _file;
    i->freq = _freq;
    i->pos  = _pos;

    return i;
}

void delete_ii( IIndex i ) {
    free(i->key);
    free(i);
}

char* getKey( IIndex i ) {
    return i->key;
}

int* getFile( IIndex i ) {
    return &i->file;
}

int* getFreq( IIndex i ) {
    return &i->freq;
}

int* getPos( IIndex i ) {
    return &i->pos;
}

void setKey( IIndex i, char* key ) {
    strcpy( i->key, key );
}

void setFile( IIndex i, int file ) {
    i->file = file;
}

void setFreq( IIndex i, int freq ) {
    i->freq = freq;
}

void setPos( IIndex i, int pos ) {
    i->pos = pos;
}

bool isEqual( IIndex a, IIndex b ) {
    return strcmp(a->key, b->key) == 0 && a->file == b->file;
}

bool compare( IIndex a, IIndex b ) {

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

void update_frequency( char* partialPath, char* indexPath ) {

    FILE *indexFile, *partialFile, *reader;

    IIndex last = new_empty(),
           crnt = new_empty(),
           ii   = new_empty();

    reader      = open_file( partialPath, "r" );
    partialFile = open_file( partialPath, "r" );
    indexFile   = open_file( indexPath,   "w" );

    int frequency = 1, readCounter = 0, writeCounter = 0;

    fscanf(partialFile, "%s %d %d", getKey(last), getFile(last), getPos(last));
    readCounter++;

    while ( writeCounter != readCounter ) {

        if ( fscanf(partialFile, "%s %d %d", getKey(crnt), getFile(crnt), getPos(crnt)) != EOF )
            readCounter++;

        if ( !isEqual( last, crnt ) || feof(partialFile) ) {

            for ( int i = 0; i < frequency; i++ ) {
                fscanf ( reader,    "%s %d %d",      getKey(ii),  getFile(ii), getPos(ii)             );
                fprintf( indexFile, "%s,%d,%d,%d\n", getKey(ii), *getFile(ii), frequency, *getPos(ii) );
                writeCounter++;
            }

            setKey  ( last,  getKey (crnt) );
            setFile ( last, *getFile(crnt) );
            setPos  ( last, *getPos (crnt) );
            frequency = 1;
        }
        else {
            frequency++;
        }
    }

    close_file( reader      );
    close_file( partialFile );
    close_file( indexFile   );

    delete_ii( last );
    delete_ii( crnt );
    delete_ii( ii   );
}

void make_index( int *_n, long long int *_memSize, const char* _chatsPaths, const char* _indexPath ) {

    mkdir(TMP_PATH, 0777);

    int fileCount    = sort_chats  ( _n, _memSize, _chatsPaths );
    int partialIndex = merge_files ( fileCount );

    char *indexFilePath   = ( char* ) malloc( PATH_SIZE     * sizeof( char ) ),
         *partialFilePath = ( char* ) malloc( TMP_PATH_SIZE * sizeof( char ) );

    sprintf( partialFilePath, "%s%d", TMP_PATH, partialIndex );
    sprintf( indexFilePath,   "%sindex", _indexPath );

    update_frequency( partialFilePath, indexFilePath );

    free( indexFilePath   );
    free( partialFilePath );
}
