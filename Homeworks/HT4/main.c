#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

const int size = 4096;

int main(int argc, char** argv) {
    int fd;
    char buffer[size];
    ssize_t read_bytes;
    fd = open(argv[1], O_RDONLY);
    read_bytes = read(fd, buffer, size);
    close(fd);
    int output;
    output = open(argv[2], O_WRONLY | O_CREAT, 0666);
    int len;
    len = write(output, buffer, read_bytes);
    close(output);
    return 0;
}
