#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    pid_t pid = fork();
    int n = atoi(argv[1]);
    if (pid == 0) {
        int fact = 1;
        for (int i = 2; i <= n; ++i) {
            fact *= i;
        }
        printf("Child process has finished. Factorial value: %d\n", fact);
    } else {
        int fib1 = 1, fib2 = 1;
        for (int i = 3; i <= n; ++i) {
            int tmp = fib1 + fib2;
            fib1 = fib2;
            fib2 = tmp;
        }
        printf("Parent process has finished. Fibbonachi value: %d\n", fib2);
    }
    return 0;
}
