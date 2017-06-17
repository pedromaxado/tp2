#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <file_handler.h>
#include <external_sort.h>
#include <internal_sort.h>
#include <inverted_index.h>

#define CHAT_ONE 1
#define CHAT_TWO -1

#define STRING_MAX "~"
#define INF INT_MAX

int merge_files( const int _fileCount ) {

    FILE *chatOneFile, *chatTwoFile, *outFile;

    char *chatOnePath = ( char* ) malloc( TMP_PATH_SIZE * sizeof(char) ),
         *chatTwoPath = ( char* ) malloc( TMP_PATH_SIZE * sizeof(char) ),
         *outPath     = ( char* ) malloc( TMP_PATH_SIZE * sizeof(char) );

    chatOnePath[0] = chatTwoPath[0] = outPath[0] = '\0';

    int chatOneNum  = 0,
        chatTwoNum  = 1,
        outNum      = _fileCount,
        endFileNum  = ( _fileCount - 1 ) * 2;

    IIndex i1 = new_empty(),
           i2 = new_empty();

    while ( chatTwoNum <= endFileNum ) {

        sprintf( chatOnePath, "%s%d", TMP_PATH, chatOneNum );
        sprintf( chatTwoPath, "%s%d", TMP_PATH, chatTwoNum );
        sprintf( outPath,     "%s%d", TMP_PATH, outNum     );

        chatOneFile = open_file(chatOnePath, "r");
        chatTwoFile = open_file(chatTwoPath, "r");
        outFile     = open_file(outPath,     "w");

        FILE* nextFile;
        IIndex nextI;

        fscanf( chatOneFile, "%s %d %d", getKey(i1), getFile(i1), getPos(i1) );
        fscanf( chatTwoFile, "%s %d %d", getKey(i2), getFile(i2), getPos(i2) );

        int i1_from = CHAT_ONE,
            i2_from = CHAT_TWO;

        while ( strcmp( getKey(i1), STRING_MAX ) != 0 || strcmp( getKey(i2), STRING_MAX ) != 0 ) {

            if ( compare(i1, i2) ) {
                fprintf(outFile, "%s %d %d\n", getKey(i1), *getFile(i1), *getPos(i1));

                nextI = i1;

                if ( i1_from == CHAT_ONE )
                    nextFile = chatOneFile;
                else
                    nextFile = chatTwoFile;
            }
            else {
                fprintf(outFile, "%s %d %d\n", getKey(i2), *getFile(i2), *getPos(i2));

                nextI = i2;

                if ( i2_from == CHAT_ONE )
                    nextFile = chatOneFile;
                else
                    nextFile = chatTwoFile;
            }

            if ( fscanf(nextFile, "%s %d %d", getKey(nextI), getFile(nextI), getPos(nextI)) == EOF ) {
                setKey ( nextI, STRING_MAX );
                setFile( nextI, INF        );
                setPos ( nextI, INF        );
            }
        }

        close_file( chatOneFile );
        close_file( chatTwoFile );
        close_file( outFile     );

        chatOneNum += 2;
        chatTwoNum += 2;
        outNum++;
    }

    delete_ii(i1);
    delete_ii(i2);

    free( chatOnePath );
    free( chatTwoPath );
    free( outPath     );

    return endFileNum;
}

int sort_chats( int *_n, int *_memSize, const char* _chatsPath ) {

    FILE *chatFile,
         *output;

    char *chatPath = ( char* ) malloc( PATH_SIZE     * sizeof(char) ),
         *outPath  = ( char* ) malloc( TMP_PATH_SIZE * sizeof(char) );

    int i,
        chunk,
        chunkSize   = *_memSize / II_SIZE,
        fileCounter = 0;

    IIndex *iiArray = ( IIndex* ) malloc( chunkSize * sizeof( IIndex ) );

    for ( i = 0; i < chunkSize; i++ )
        iiArray[i] = new_empty();

    for ( i = 1; i <= *_n; i++ ) {
        sprintf( chatPath, "%s%d", _chatsPath, i );

        chatFile = open_file(chatPath, "r");

        while ( !feof(chatFile) ) {
            chunk = 0;

            while ( chunk < chunkSize && fscanf(chatFile, "%s", getKey(iiArray[chunk])) != EOF ) {
                setFile( iiArray[chunk], i );
                setPos ( iiArray[chunk], ftell(chatFile) - strlen(getKey(iiArray[chunk])) );

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
