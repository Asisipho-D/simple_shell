#include "Shell.h"

/**
 * _myexit - exits the shell
 * @details: structure containing potential arguments. used to maintain constant function prototype.
 * Return: exits with a given exit status (0) if details.argv[0] != "exit"
 */
int _myexit(details_t *details)
{
	int exitcheck;

	if (details->argv[1])  /* if there is an exit argument */
	{
		exitcheck = _erratoi(details->argv[1]);
		if (exitcheck == -1)
		{
			details->status = 2;
			print_error(details, "illegal number");
			_eputs(details->argv[1]);
			return (1);
		}
		details->err_num = -1;
		return (-2);
	}
}

/**
 * _mycd - changes the current directory of the process
 * @details: structure containing potential arguments. used to maintain constant function prototype.
 * Return: always 0
 */
int _mycd(details_t *details)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!details->argv[1])
	{
		dir = _getenv(details, "HOME=");
		if (!dir)
			chdir ret = /* TODO: What should this be? */
				chdir((dir = _getenv(details, "PWD="))? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(details->argv[1], "-") == 0)
	{
		if (!_getenv(details, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(details, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: What should this be? */
			chdir((dir = _getenv(details, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(details->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(details, "can't cd to ");
		_puts(details->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(details, "OLDPWD", _getenv(details, "PWD="));
		_setenv (details, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @details: structure containing potential arguments. used to maintain constant function prototype.
 * Return: always 0
 */
int _myhelp(details_t *details)
{
	char **arg_array;

	arg_array = details->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
