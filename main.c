#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define SECTOR_SIZE 512

void read_sector(const char *path)
{
    int fd;
    int buf_len = SECTOR_SIZE;
    char buf[buf_len];
    char *buf_ptr = buf;
    ssize_t ret;

    fd = open(path, O_RDONLY);
    if(fd == -1)
        printf("open file failed.");

    while( buf_len != 0 && (ret = read(fd, buf_ptr, buf_len)) != 0 )
    {
        if(ret == -1)
        {
            if(errno == EINTR)
                continue;
            printf("read");
            break;
        }
        buf_len -= ret;
        buf_ptr += ret;
    }

    for(int i = 0; i < SECTOR_SIZE; i++)
    {
        printf("%02x ", (unsigned char)buf[i]);
        if(((i + 1) % 16) == 0)
            printf("\n");
    }
    printf("\n");

    close(fd);

    return;
}


typedef int ul_excl_t[16];

#define UL_BUILD_BUG_ON_ZERO(e) __extension__ (sizeof(struct { int:-!!(e); }))

int main()
{
    //const char *disk = "/dev/sdc";
    const char *disk = "/dev/sdj";
    //read_sector(disk);

    struct s_t {
        char *des;
        int id;
    };

    struct s_t s[] = {
        [0] = {"index: 0", 0},
        [1] = {"index: 1", 1},
        [5] = {"index: 5", 5}
    };

    /*printf("%s\n", s[3].des);
    printf("%s\n", s[5].des);*/

    printf("%d\n", 1 << 4);

    return 0;
}
