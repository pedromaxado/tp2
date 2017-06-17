#include <stdio.h>
#include <stdlib.h>
#include <inverted_index.h>

int main() {

    int *n;
    long long int *memSize;
    char chats[PATH_SIZE];
    char index[PATH_SIZE];

    n = ( int* ) malloc( sizeof(int) );
    memSize = ( long long int* ) malloc( sizeof( long long int ) );

    scanf( "%d",   n       );
    scanf( "%lld", memSize );
    scanf( "%s",   chats   );
    scanf( "%s",   index   );

    make_index( n, memSize, chats, index );

    free(n);
    free(memSize);

    return 0;
}
