#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <inverted_index.h>

struct inverted_index {
    char *key;
    int file,
        freq,
        pos;
};

InvertedIndex new_InvertedIndex( char* _key, int _file, int _freq, int _pos ) {
    InvertedIndex i = ( InvertedIndex ) malloc( sizeof( struct inverted_index ) );

    strcpy(i->key, _key);
    i->file = _file;
    i->freq = _freq;
    i->pos  = _pos;

    return i;
}

void updateFrequency( const char* word, int fileNumber ) {

    FILE* fp;

    char *wordFileNumb = ( char* ) malloc( MAX_FILES * sizeof(char) );
    char *wordFreqFile = ( char* ) malloc( PATH_SIZE * sizeof(char) );

    int freq = 1;

    wordFreqFile[0] = '\0';

    sprintf(wordFileNumb, "%d", fileNumber);

    strcat( wordFreqFile, TMP_PATH     );
    strcat( wordFreqFile, word         );
    strcat( wordFreqFile, wordFileNumb );

    if ( access( wordFreqFile, R_OK ) == 0 ) {
        fp = fopen( wordFreqFile, "r" );

        fscanf( fp, "%d", &freq );
        freq++;

        fclose(fp);
    }

    fp = fopen( wordFreqFile, "w" );
    printf("%d\n", freq);
    fprintf(fp, "%d\n", freq);

    free(wordFileNumb);
    free(wordFreqFile);
    fclose(fp);
}

void make_index( int _n, const char* _chats, const char* _index ) {

    FILE *indexFile, *chatFile;

    char *chatFileNumb = ( char* ) malloc( MAX_FILES * sizeof(char) );
    char *chatFileName = ( char* ) malloc( PATH_SIZE * sizeof(char) );

    char *word = ( char* ) malloc( STRING_SIZE * sizeof(char) );

    chatFileName[0] = '\0';

    if ( (indexFile = fopen(_index, "w")) == NULL )
        return;

    for ( int i = 1; i <= _n; i++ ) {
        sprintf( chatFileNumb, "%d", i );

        strcat ( chatFileName, _chats       );
        strcat ( chatFileName, chatFileNumb );

        if ( (chatFile = fopen(chatFileName, "r")) == NULL )
            return;

        while ( fscanf(chatFile, "%s", word) != EOF ) {
            fprintf(indexFile, "%s,%d,1,%ld\n", word, i, ftell(chatFile)-strlen(word));
            updateFrequency( word, i );
        }

        fclose(chatFile);
        chatFileName[0] = '\0';
    }

    fclose(indexFile);

    free(chatFileNumb);
    free(chatFileName);
    free(word);
}
