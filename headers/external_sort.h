#ifndef EXTERNAL_SORT_H_
#define EXTERNAL_SORT_H_

#define TMP_PATH "./tmp/"
#define AUX_INDEX_PATH "./tmp/aux_index"

void merge_files( const int _fileCount );

int sort_chats( int *_n, int *_memSize, const char* _chatsPath );

#endif
