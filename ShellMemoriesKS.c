#include "shell.h"

/**
 * pntr_free - Frees a pointer and makes address NULL
 * @pntr: Pointer address to free
 * Return: Returns 1 if freed, otherwise returns 0.
 */

int pntr_free(void **pntr)
{
	if (pntr && *pntr)
	{
		free(*pntr);
		*pntr = NULL;
		return (1);
	}
	return (0);
}
