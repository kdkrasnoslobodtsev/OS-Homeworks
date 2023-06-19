#include <stddef.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SWR "/semaphore_writer"
#define SR "/semaphore_reader"

int main(int argc, char* argv[]) {
    char buffer[6];
    sem_t *sem_writer;
    sem_t *sem_reader;
    size_t size = strlen(argv[1]);
    size_t i = 0;
    FILE* input;
    sem_writer = sem_open("/writersem", O_CREAT, S_IRUSR | S_IWUSR, 0);
    sem_reader = sem_open("/readersem", O_CREAT, S_IRUSR | S_IWUSR, 0);
    while (i < size) {
        input = fopen("input.txt", "w");
        if (i + 5 < size) {
            for (size_t j = 0; j < 5; ++j) {
                buffer[j] = argv[1][i + j];
            }
            buffer[5] = '\0';
            fprintf(input, "%s", buffer);
            fprintf(stdout, "Writer wrote %s\n", buffer);
            i += 5;
        } else {
            for (size_t j = 0; j < size - i; ++j) {
                buffer[j] = argv[1][i + j];
            }
            for (size_t j = size - i; j <= 5; ++j) {
                buffer[j] = '\0';
            }
            fprintf(input, "%s", buffer);
            fprintf(stdout, "Have writen: %s\n", buffer);
            i = size;
        }
        fclose(input);
        sem_post(sem_reader);
        sem_wait(sem_writer);
    }
    input = fopen("input.txt", "w");
    fprintf(input, "exit\n");
    fclose(input);
    sem_post(sem_reader);
    sem_wait(sem_writer);
    sem_close(sem_writer);
    sem_close(sem_reader);
    sem_unlink(SWR);
    sem_unlink(SR);
    
    fprintf(stdout, "The end\n");
}
