#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv) {
    int fd;
    mkfifo(argv[1], 0666);
    char input[256];
    char output[256];
    
    for(;;) {
        fd = open(argv[1], O_WRONLY);
        printf("Write your message:\n");
        fgets(output, 256, stdin);
        write(fd, output, strlen(output) + 1);
        close(fd);
        
        fd = open(argv[1], O_RDONLY);
        read(fd, input, 256);
        printf("You've got a new message:\n");
        printf("%s\n", input);
        close(fd);
    }
    return 0;
}
