#include "shell.h"

/**
 * print_list_str - Prints only the str element of a list_t linked list
 * @fn: The pointer to first node
 * Return: Returns size of list
 */

size_t print_list_str(const list_t *fn)
{
	size_t xk = 0;

	while (fn)
	{
		_puts(fn->str ? fn->str : "(nil)");
		_puts("\n");
		fn = fn->next;
		xk++;
	}
	return (xk);
}

/**
 * add_node - Adds a node to start of list
 * @ahd: The address of pointer to head node
 * @str: The str field of node
 * @numb: The node index used by history
 * Return: Returns size of list
 */

list_t *add_node(list_t **ahd, const char *str, int numb)
{
	list_t *new_head;

	if (!ahd)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	memory_set((void *)new_head, 0, sizeof(list_t));
	new_head->numb = numb;
	if (str)
	{
		new_head->str = str_dup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *ahd;
	*ahd = new_head;
	return (new_head);
}

/**
 * free_list - Frees all nodes of the list
 * @ahd_ptr: The head node pointer address
 * Return: Returns void
 */

void free_list(list_t **ahd_ptr)
{
	list_t *node, *next_node, *ahd;

	if (!ahd_ptr || !*ahd_ptr)
		return;
	ahd = *ahd_ptr;
	node = ahd;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*ahd_ptr = NULL;
}

/**
 * add_node_end - Adds a node to the end of the list
 * @ahd: The address of pointer to head node
 * @str: The str field of node
 * @numb: The node index used by history
 * Return: Returns size of list
 */

list_t *add_node_end(list_t **ahd, const char *str, int numb)
{
	list_t *new_node, *node;

	if (!ahd)
		return (NULL);

	node = *ahd;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	memory_set((void *)new_node, 0, sizeof(list_t));
	new_node->numb = numb;
	if (str)
	{
		new_node->str = str_dup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*ahd = new_node;
	return (new_node);
}

/**
 * delete_node_at_index - Deletes node at given index
 * @ahd: First node pointer address
 * @idx: Index of node to delete
 * Return: Returns 1 on success, returns 0 on failure
 */

int delete_node_at_index(list_t **ahd, unsigned int idx)
{
	list_t *node, *prev_node;
	unsigned int xk = 0;

	if (!ahd || !*ahd)
		return (0);

	if (!idx)
	{
		node = *ahd;
		*ahd = (*ahd)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *ahd;
	while (node)
	{
		if (xk == idx)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		xk++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}
