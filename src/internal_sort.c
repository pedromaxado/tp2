#include <inverted_index.h>
#include <internal_sort.h>

void swap( InvertedIndex* a, InvertedIndex* b ) {
    InvertedIndex aux = *a;

    *a = *b;
    *b = aux;
}

int partition( InvertedIndex* vec, int p, int r ) {

    InvertedIndex pivot = vec[r];
    int i = p-1;

    for( int j = p; j <= r-1; j++ ) {
        if ( compare(vec[j], pivot) ) {
            i++;
            swap( &vec[i], &vec[j] );
        }
    }

    swap( &vec[i+1], &vec[r] );

    return i+1;
}

void quick_sort( InvertedIndex* vec, int p, int r ) {

    if ( p < r ) {
        int q = partition( vec, p, r );
        quick_sort( vec, p, q-1 );
        quick_sort( vec, q+1, r );
    }
}
