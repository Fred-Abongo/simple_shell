#include "shell.h"

/**
 * memory_set - Pointes memory with a constant byte
 * @m: The memory area pointer
 * @b: The byte to filled with *m
 * @n: The bytes amount to be filled
 * Return: Returns (m) a pointer to the m memory area
 */

char *memory_set(char *m, char b, unsigned int n)
{
	unsigned int xs;

	for (xs = 0; xs < n; xs++)
		m[xs] = b;
	return (m);
}

/**
 * str_free - Frees string of strings
 * @s: A string of strings
 */

void str_free(char **s)
{
	char **as = s;

	if (!s)
		return;
	while (*s)
		free(*s++);
	free(as);
}

/**
 * mem_realloc - Reallocates the memory block
 * @ptr: The previous malloc'ated block pointer
 * @ol_size: The previous block byte size
 * @nw_size: The new block byte size
 * Return: Returns old'block nameen pointer.
 */

void *mem_realloc(void *ptr, unsigned int ol_size, unsigned int nw_size)
{
	char *ss;

	if (!ptr)
		return (malloc(nw_size));
	if (!nw_size)
		return (free(ptr), NULL);
	if (nw_size == ol_size)
		return (ptr);

	ss = malloc(nw_size);
	if (!ss)
		return (NULL);

	ol_size = ol_size < nw_size ? ol_size : nw_size;
	while (ol_size--)
		ss[ol_size] = ((char *)ptr)[ol_size];
	free(ptr);
	return (ss);
}
