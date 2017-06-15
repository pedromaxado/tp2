#include <stdio.h>
#include <inverted_index.h>

int main() {

    int n, memSize;
    char chats[PATH_SIZE];
    char index[PATH_SIZE];

    scanf("%d", &n);
    scanf("%d", &memSize);

    scanf("%s", chats);
    scanf("%s", index);

    make_index( n, memSize, chats, index );

    return 0;
}
