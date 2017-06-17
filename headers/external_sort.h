#ifndef EXTERNAL_SORT_H_
#define EXTERNAL_SORT_H_

#define TMP_PATH "./tmp/"

int merge_files( const int _fileCount );

int sort_chats( int *_n, long long int *_memSize, const char* _chatsPath );

#endif
