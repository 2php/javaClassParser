#include "javaclp.h"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        exit(1);
    }

    // Open file
    int fd = open(argv[1], O_RDONLY);
    if (fd  == -1) { err("open"); }

    size_t fsize = get_filesize(fd);

    // Execute mmap
    void* mem = mmap(NULL, fsize, PROT_READ, MAP_SHARED, fd, 0);
    if (mem == (char*)-1) { err("mmap"); }
    madvise(mem, fsize, MADV_SEQUENTIAL);

    // Holders
    u_int32_t u4;
    u_int16_t u2;
    u_int8_t u1;
    u_int16_t constant_pool_count;

    // Iterator
    byte *mei = mem;

    printf("ClassFile {\n");

    leread(&u4, 4, &mei);
    printf("\tmagic:\t\t\t0x%08x\n", u4);

    leread(&u2, 2, &mei);
    printf("\tminor_version:\t\t0d%04d\n", u2);
    leread(&u2, 2, &mei);
    printf("\tmajor_version:\t\t0d%04d\n", u2);

    leread(&constant_pool_count, 2, &mei);
    printf("\tconstant_pool_count:\t0d%04d\n", constant_pool_count);

    for (int i = 0; i < constant_pool_count; i++)
    {
        printf("\tcp_info {\n");
        leread(&u1, 1, &mei);
        printf("\t\ttag: 0d%02d\n", u1);
        printf("\t}\n");
    }

    printf("}\n");

    // Cleanup
    if (munmap(mem, fsize))
    {
        perror("munmap");
        exit(1);
    }
    close(fd);
}
