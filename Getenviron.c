#include "Shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @details: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(details_t *details)
{
	if (!details->environ || details->env_changed)
	{
		details->environ = list_to_strings(details->env);
		details->env_changed = 0;
	}

	return (details->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @details: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(details_t *details, char *var)
{
	List_t *node = details->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			details->env_changed = delete_node_@index(&(details->env), i);
			i = 0;
			node = details->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (details->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @details: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(details_t *details, char *var, char *value)
{
	char *buf = NULL;
	List_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = details->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(details->env), buf, 0);
	free(buf);
	details->env_changed = 1;
	return (0);
}
