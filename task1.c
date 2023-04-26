#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROMPT "#cisfun$ "

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    while (1) {
        printf("%s", PROMPT);
        nread = getline(&line, &len, stdin);
        if (nread == -1) { // end of file (Ctrl+D)
            break;
        }
        if (line[nread - 1] == '\n') { // remove trailing newline
            line[nread - 1] = '\0';
        }
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // child process
            char *argv[] = { line, NULL };
            execve(line, argv, NULL);
            perror(line);
            exit(EXIT_FAILURE);
        } else {
            // parent process
            int status;
            waitpid(pid, &status, 0);
        }
    }

    free(line);
    exit(EXIT_SUCCESS);
}
