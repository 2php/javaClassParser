#include "javaclp.h"
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#define MEMSIZE 100000000

using namespace std;

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        exit(1);
    }

    struct stat finfo;
    if (stat(argv[1], &finfo) == -1) { return 0; }

    int fd = open(argv[1], O_RDONLY);
    if (fd  == -1) { return 0; }

    void* mem = mmap(NULL, MEMSIZE, PROT_READ, MAP_SHARED, fd, 0);
    if (mem == (char*)-1) { return 0; }

    madvise(mem, finfo.st_size, MADV_SEQUENTIAL);

    void *ptr = mem;    
}
