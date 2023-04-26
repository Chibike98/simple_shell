#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFSIZE 1024

int main(void)
{
    char *buffer;
    size_t bufsize = BUFSIZE;
    int status;
    pid_t pid;

    buffer = (char *)malloc(bufsize * sizeof(char));
    if (buffer == NULL) {
        perror("Error allocating buffer");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("$ ");
        getline(&buffer, &bufsize, stdin);

        // Check for EOF
        if (feof(stdin)) {
            printf("\n");
            exit(EXIT_SUCCESS);
        }

        // Remove newline character
        buffer[strcspn(buffer, "\n")] = '\0';

        if (strlen(buffer) > 0) {
            pid = fork();
            if (pid == 0) {
                // Child process
                if (execve(buffer, NULL, NULL) == -1) {
                    printf("Command not found\n");
                    exit(EXIT_FAILURE);
                }
            } else if (pid < 0) {
                // Error forking
                perror("Error forking");
            } else {
                // Parent process
                waitpid(pid, &status, 0);
            }
        }
    }
    free(buffer);
    return 0;
}
