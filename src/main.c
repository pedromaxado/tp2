#include <stdio.h>
#include <string.h>
#include <inverted_index.h>

int main() {

    int n, memSize;
    char chats[PATH_SIZE];
    char index[PATH_SIZE];

    scanf("%d", &n);
    scanf("%d", &memSize);

    scanf("%s", chats);
    scanf("%s", index);

    strcat( index, "index" );

    make_index( n, chats, index );

    return 0;
}
