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

    while( buf_len !=0 && (ret = read(fd, buf_ptr, buf_len)) != 0 )
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

    int a = 0;
    for(int i = 0; i < SECTOR_SIZE; i++)
    {
        printf("%02x ", buf[i]);
        if((++a % 16) == 0)
            printf("\n");
    }
    printf("\n");

    close(fd);

    return;
}

int main()
{
    const char *disk = "/dev/sdc";

    read_sector(disk);

    return 0;
}