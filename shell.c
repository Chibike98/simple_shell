#include "main.h"

/**
 * main - Entry point of the program
 *
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
        char *buffer = NULL;
        size_t bufsize = 0;
        ssize_t nread;
        char *command;
        char *args[2];
        int status;

        while (1)
        {
                printf("#cisfun$ ");
                nread = getline(&buffer, &bufsize, stdin);
                if (nread == -1)
                {
                        printf("\n");
                        break;
                }
                command = strtok(buffer, "\n");
                args[0] = command;
                args[1] = NULL;
                if (fork() == 0)
                {
                        char *path = getenv("PATH");
                        char *dir;
                        char cmd_path[1024];

                        while ((dir = strtok(path, ":")) != NULL)
                        {
                                snprintf(cmd_path, sizeof(cmd_path), "%s/%s", dir, command);
                                if (access(cmd_path, X_OK) == 0)
                                {
                                        args[0] = cmd_path;
                                        break;
                                }
                                path = NULL;
                        }

                        if (execve(args[0], args, NULL) == -1)
                        {
                                fprintf(stderr, "%s: No such file or directory\n", args[0]);
                                exit(1);
                        }
                }
                else
                {
                        wait(&status);
                }
        }

        free(buffer);

        return (0);
}
