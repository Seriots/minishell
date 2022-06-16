/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:18:54 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/15 19:13:34 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include "../../include/minishell.h"
#include "../../include/libft.h"
#include "../../include/ft_printf.h"

/*
* cd builtin command, change the current directory to current_directory/path
* on error, return -1 and set errno.
*/
static char	*get_path(t_shell *shell,
		char **arguments, size_t argc)
{
	t_dict	*home_path;

	if (argc == 0)
	{
		home_path = dict_getelem_key(shell->env, "HOME");
		if (home_path)
			return (home_path->value);
		else
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (0);
		}
	}
	else
		return (arguments[0]);
}

char	*ft_malloc_str(const char *str)
{
	char	*result;

	result = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	if (!result)
		return (0);
	ft_strlcpy(result, str, ft_strlen(str) + 1);
	return (result);
}

static int	update_pwd(t_shell **shell, char *path)
{
	t_dict	*pwd;
	t_dict	*oldpwd;
	char	*new_path;
	size_t	size;

	pwd = dict_getelem_key((*shell)->env, "PWD");
	oldpwd = dict_getelem_key((*shell)->env, "OLDPWD");
	if (!pwd)
		return (-1);
	if (oldpwd)
	{
		free(oldpwd->value);
		oldpwd->value = pwd->value;
	}
	else
	{
		oldpwd = dict_new(ft_malloc_str("OLDPWD"), pwd->value);
		dict_add_back(&(*shell)->env, oldpwd, free, free);
	}
	size = ft_strlen(path);
	new_path = ft_calloc(sizeof(char), size + 1);
	if (!new_path)
		return (-1);
	ft_strlcpy(new_path, path, size + 1);
	pwd->value = new_path;
	return (0);
}

int	is_minus(t_shell **shell)
{
	char	*wit;
	t_dict	*pwd;
	t_dict	*oldpwd;
	
	pwd = dict_getelem_key((*shell)->env, "PWD");
	oldpwd = dict_getelem_key((*shell)->env, "OLDPWD");
	if (!pwd)
	{
		ft_putstr_fd("cd: PWD not set\n", 2);
		return (-1);
	}
	if (!oldpwd)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return (-1);
	}
	wit = pwd->value;
	pwd->value = oldpwd->value;
	oldpwd->value = wit;
	if (pwd->value)
		ft_printf("%s\n", pwd->value);
	return (0);
}

int	cd_command(t_shell *shell, char **arguments)
{
	int		error;
	char	*path;
	size_t	argc;
	char	*error_message;

	argc = ft_arraylen(arguments);
	if (argc > 1)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (-1);
	}
	if (argc == 1 && !ft_strncmp(arguments[0], "-", ft_strlen(arguments[0])))
		return (is_minus(&shell));
	path = get_path(shell, arguments, argc);
	if (path)
	{
		error = chdir(path);
		if (error)
		{
			error_message = ft_strjoin("cd: ", path);
			perror(error_message);
			free(error_message);
			return (error);
		}
		free(shell->directory);
		shell->directory = get_current_directory();
		if (update_pwd(&shell, shell->directory))
			return (-1);
		if (!shell->directory)
			return (-1);
	}
	return (0);
}

/*
int	main(int argc, char *argv[], char **env)
{
	t_shell	shell;

	init_shell(&shell, env);
	argv = &argv[1];
	cd_command(&shell, argv);
}*/
