#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

int main() {
    int *shm;
    int shmid;
    key_t key;
    key = ftok("server.c", 0);
    if ((shmid = shmget(key, sizeof(int), 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
        if (errno != EEXIST) {
            printf("shmget error\n");
            exit(-1);
        }
        shmid = shmget(key, sizeof(int), 0);
    }
    shm = (int *)shmat(shmid, NULL, 0);
    srand(time(NULL));
    shm[0] = rand() % 10 + 1;    
    return 0;
}
