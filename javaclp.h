#include "tags.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

typedef u_int8_t byte;

static inline void err(const char* str)
{
    perror(str);
    exit(1);
}

size_t get_filesize(const int fd)
{
    struct stat sb;
    if (fstat(fd, &sb) == -1) { err("fstat"); }
    return sb.st_size;
}

// TODO: implement endian independent mmap read in x86 assembly
size_t rvread(byte *ptr, size_t size, byte *mem)
{
    int i;
    for (i = 0; i < size; i++)
    {
        byte b = *(mem + i);
        if (b == EOF) { break; }

        *(ptr + size-1 - i) = b;
    }
    return i;
}

// Wrapper for rvread such that mem pointer is moved with read
static inline void leread(void *u, size_t s, byte **m) { *m += rvread((byte*)u, s, *m); }

extern size_t eiberead(byte *ptr, size_t size, byte *mem);
