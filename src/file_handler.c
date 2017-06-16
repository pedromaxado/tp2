#include <stdio.h>
#include <stdlib.h>
#include <file_handler.h>

FILE* open_file( char* path, char* mode ) {

    FILE* fp;

    if ( (fp = fopen(path, mode)) == NULL ) {
        printf("deu ruim %s\n", path);
        exit(EXIT_FAILURE);
    }

    return fp;
}

void close_file( FILE* fp ) {

    if ( fp )
        fclose(fp);
}

void write_ii( FILE* fp, IIndex i ) {
    fprintf(fp, "%s,%d,%d,%d\n", getKey(i), *getFile(i), *getFreq(i), *getPos(i));
}

void write_partial_ii( FILE* fp, IIndex i ) {
    fprintf(fp, "%s %d %d\n", getKey(i), *getFile(i), *getPos(i));
}
