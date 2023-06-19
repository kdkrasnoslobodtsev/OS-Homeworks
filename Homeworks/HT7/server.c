#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(int argc, char** argv) {
    int fd;
    char* ch;
    fd = shm_open("shared", O_RDWR | O_CREAT, 0777);
    ftruncate(fd, 1);
    ch = mmap(NULL, 1, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    sleep(5);
    for (int i = 0; i < 25; ++i) {
        printf("%d\n", ch[0]);
        sleep(3);
    }
    shm_unlink("shared");
    return 0;
}
