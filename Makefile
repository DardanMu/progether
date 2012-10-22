CC=gcc

debug_build:

gcc -std=gnu99 -o debug_build src/progether.c lib/defines.h lib/libMemInfo.h lib/libNetworkingInfo.h -I lib

