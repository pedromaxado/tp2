#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <file_handler.h>
#include <external_sort.h>
#include <internal_sort.h>
#include <inverted_index.h>

void merge_files( const int _fileCount ) {

    FILE *chatOneFile, *chatTwoFile, *outFile;

    char *chatOnePath, *chatTwoPath, *outPath;
    int chatOneNum  = 0,
        chatTwoNum  = 1,
        outNum      = _fileCount,
        endFileNum  = _fileCount-1;

    chatOnePath = ( char* ) malloc( TMP_PATH_SIZE * sizeof(char) );
    chatTwoPath = ( char* ) malloc( TMP_PATH_SIZE * sizeof(char) );
    outPath     = ( char* ) malloc( TMP_PATH_SIZE * sizeof(char) );

    while ( chatTwoNum + 2 <= endFileNum ) {

        sprintf( chatOnePath, "%s%d", TMP_PATH, chatOneNum );
        sprintf( chatTwoPath, "%s%d", TMP_PATH, chatTwoNum );
        sprintf( outPath,     "%s%d", TMP_PATH, outNum     );

        chatOneFile = open_file(chatOnePath, "r");
        chatTwoFile = open_file(chatTwoPath, "r");
        outFile     = open_file(outPath,     "w");

        chatOneNum += 2;
        chatTwoNum += 2;
    }

    free(chatOnePath);
    free(chatTwoPath);
}

int sort_chats( int *_n, int *_memSize, const char* _chatsPath ) {

    FILE *chatFile,
         *output;

    char *outPath,
         *chatPath;
    int i,
        chunk,
        chunkSize,
        fileCounter = 0;

    InvertedIndex*  iiArray;

    chatPath     = ( char* ) malloc( TMP_PATH_SIZE * sizeof(char) );
    outPath      = ( char* ) malloc( TMP_PATH_SIZE * sizeof(char) );

    chunkSize = *_memSize / II_SIZE;

    iiArray = ( InvertedIndex* ) malloc( chunkSize * sizeof( InvertedIndex ) );

    for ( i = 0; i < chunkSize; i++ )
        iiArray[i] = new_empty();

    for ( i = 1; i <= *_n; i++ ) {
        sprintf( chatPath, "%s%d", _chatsPath, i );

        chatFile = open_file(chatPath, "r");

        while ( !feof(chatFile) ) {
            chunk = 0;


            while ( chunk < chunkSize && fscanf(chatFile, "%s", getKey(iiArray[chunk])) != EOF ) {
                setFile(iiArray[chunk], i);
                setPos(iiArray[chunk], ftell(chatFile) - strlen(getKey(iiArray[chunk])) );

                chunk++;
            }

            quick_sort( iiArray, 0, chunk-1 );

            sprintf( outPath, "%s%d", TMP_PATH, fileCounter);

            output = open_file( outPath, "w" );

            for ( int k = 0; k < chunk; k++ )
                write_partial_ii(output, iiArray[k]);

            close_file(output);

            fileCounter++;
        }

        close_file(chatFile);
    }

    for ( i = 0; i < chunkSize; i++ )
        delete_ii(iiArray[i]);

    free( iiArray  );

    free( chatPath );
    free( outPath  );

    return fileCounter;
}
