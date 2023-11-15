#include "Shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded with line numbers, starting at 0.
 * @details: structure containing potential arguments. used to maintain constant function prototype.
 * Return: always 0
 */
int _myhistory(details_t *details)
{
	print_list(details->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @details: parameter struct
 * @str: the string alias
 *
 * return: always 0 on success, 1 on error
 */
int unset_alias(details_t *details, char *str)
{
	char *p, c;
	int ret;

	p= _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_@index(&(details->alias), get_node_index(details->alias, node_starts_with(details->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @details: parameter struct
 * @str: the string alias
 *
 * Return: always 0 on success, 1 on error
 */
int set_alias(details_t *details, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(details, str));

	unset_alias(details, str);
	return (add_node_end(&(details->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: always 0 on success, 1 on error
 */
int print_alias(List_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @details: structure containing potential arguments. used to maintain constant function prototype.
 * 
 * Return: always 0
 */
int _myalias(details_t *details)
{
	int i = 0;
	char *p = NULL;
	List_t *node - NULL;

	if (details->argc == 1)
	{
		node = details->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; details->argv[i]; i++)
	{
		p = _strchr(details->argv[i], '=');
		if (p)
			set-alias(details, details->argv[i]);
		else
			print_alias(node_starts_with(details->alias, details->argv[i], ' = '));
	}

	return (0);
}	
