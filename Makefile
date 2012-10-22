CC=gcc

terminote: 
	gcc -std=gnu99 -o debug_build src/progether.c lib/defines.h lib/libMemInfo.h -I lib
