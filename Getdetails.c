#include "Shell.h"

/**
 *Clear_details - initializes details_t struct
 *@details: struct address
 */
void Clear_details(details_t *details)
{
	details->arg = NULL;
	details->argv = NULL;
	details->path = NULL;
	details->argc = 0;
}

/**
 * set_details - initializez details_t struct
 * @details: struct address
 * @av: argument vector
 */
void set_details(details_t *details, char **av)
{
	int i = 0;

	details->fname = av[0];
	if (details->arg)
	{
		details->argv = strtow(details->arg, " \t");
		if (!details->argv)
		{
			details->argv = malloc(sizeof(char *) * 2);
			if (details->argv)
			{
				details->argv[0] = _strdup(details->arg);
				details->argv[1] = NULL;
			}
		}
		for (i = 0; details->argv && details->argv[i]; i++)
		{
			details->argc = i;
			replace_alias(details);
			replace_vars(details);
		}
	}
}

/**
 * free_details - frees details_t struct fields
 * @details: struct address
 * @all: tru if freeing all fields
 */
void free_details(details_t *details, int all)
{
	ffree(details->argv);
	details->argv = NULL;
	details->path = NULL;
	if (all)
	{
		if (!details->cmd_buf)
			free(details->arg);
		if (details->env)
			free_list(&(details->env));
		if (details->history)
			free_list(&(details->history));
		if (details->alias)
			free_list(&(details->alias));
		ffree(details->environ);
			details->environ = NULL;
		bfree((void **)details->cmd_buf);
		if (details->readfd > 2)
			close(details->readfd);
		_putchar(BUF_FLUSH);
	}
}
