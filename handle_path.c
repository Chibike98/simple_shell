#include "simple_shell.h"

/**
 *set_path - sets the environment variable
 *
 *Return: Nothing
 */
void set_path(void)
{
	setenv("PATH",
		"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", 1);
}

/**
 *find_command - gets the full path of the command the user enters
 *@user_input: the input supplied
 *
 *Return: Returns the full path to the command, if success
 * -------- If failed, returns NULL
 */
char *find_command(char *user_input)
{
	char *path;
	char *dir;
	char *cmd;
	char *result;

	if (access(user_input, X_OK) == 0)
	{
		result = _strdup(user_input);
		if (result == NULL)
		{
			return (NULL);
		}
		return (result);
	}
	path = getenv("PATH");
	result = malloc(MAX_USER_INPUT_LENGTH);
	if (path == NULL)
		return (NULL);
	dir = strtok(path, ":");
	while (dir != NULL)
	{
		cmd = _strcpy(result, dir);
		cmd = _strcat(cmd, "/");
		cmd = _strcat(cmd, user_input);
		if (access(cmd, X_OK) == 0)
		{
			return (result);
		}
		dir = strtok(NULL, ":");
	}
	free(result);
	return (NULL);
}
