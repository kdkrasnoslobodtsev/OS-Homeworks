#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SWR "/semaphore_writer"
#define SR "/semaphore_reader"

int main() {
    sem_t* sem_writer;
    sem_t* sem_reader;
    FILE* input;
    char buffer[6];
    sem_writer = sem_open("/writersem", O_CREAT, S_IRUSR | S_IWUSR, 0);
    sem_reader = sem_open("/readersem", O_CREAT, S_IRUSR | S_IWUSR, 0);
    while (1) {
        sem_wait(sem_reader);
        input = fopen("input.txt", "r");
        fread(buffer, 1, 6, input);
        if (strcmp(buffer, "exit\n") == 0) {
            fclose(input);
            sem_post(sem_writer);
            sem_close(sem_writer);
            sem_close(sem_reader);
            break;
        }
        fprintf(stdout, "Got text: %s\n", buffer);
	for (int i = 0; i < 6; ++i) {
	    buffer[i] = '\0';
	}
        fclose(input);
        sem_post(sem_writer);
    }
    return 0;
}
