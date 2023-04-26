#include "simple_shell.h"

/**
 * _strcat - concatenates two string in a path form
 * @dest: the string unto which another string will be added
 * @src: the string to be added
 *
 * Return: (Success) pointer to the destination string
 *
 */
char *_strcat(char *dest, const char *src)
{
	char *ptr = dest + strlen(dest);

	while (*src != '\0')
	{
		*ptr++ = *src++;
	}
	*ptr = '\0';
	return (dest);
}

/**
 * handle_signal - handle the process interrept signal
 * @identifier: the signal identifier
 *
 * Return: void
 */
void handle_signal(int identifier)
{
	if (identifier == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 4);
		write(STDOUT_FILENO, "$", 3);
	}
}
