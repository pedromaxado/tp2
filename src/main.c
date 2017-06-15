#include <stdio.h>
#include <stdlib.h>
#include <inverted_index.h>

int main() {

    int *n, *memSize;
    char chats[PATH_SIZE];
    char index[PATH_SIZE];

    n = ( int* ) malloc( sizeof(int) );
    memSize = ( int* ) malloc( sizeof(int) );

    scanf("%d", n);
    scanf("%d", memSize);

    scanf("%s", chats);
    scanf("%s", index);

    make_index( n, memSize, chats, index );

    free(n);
    free(memSize);

    return 0;
}
