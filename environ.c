#include "Shell.h"

/**
 * _myenv - prints the current environment
 * @details: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(details_t *details)
{
	print_list_str(details->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @details: Structure containing potential arguments. Used to maintain
 * @name: the environ variable name
 *
 * Return: always NULL
 */
char *_getenv(details_t *details, const char *name)
{
	List_t *node = details->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @details: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(details_t *details)
{
	if (details->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(details, detailso->argv[1], details->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @details: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(details_t *details)
{
	int i;

	if (details->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= details->argc; i++)
		_unsetenv(details, details->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @details: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(details_t *details)
{
	List_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	details->env = node;
	return (0);
}
