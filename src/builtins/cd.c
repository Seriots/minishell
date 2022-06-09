/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:18:54 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/08 22:45:44 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include "../../include/minishell.h"
#include "../../include/libft.h"

/*
* cd builtin command, change the current directory to current_directory/path
* on error, return -1 and set errno.
*/
static char	*get_path(char **path, t_shell *shell, char **arguments, size_t argc)
{
	if (argc == 0)
		*path = ft_dictgetelem_key(shell->env, "HOME")->value;
	else
		*path = arguments[0];
	return (*path);
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
	error = chdir(get_path(&path, shell, arguments, argc));
	if (error)
	{
		error_message = ft_strjoin("cd: ", path);
		perror(error_message);
		free(error_message);
		return (error);
	}
	free(shell->directory);
	shell->directory = get_current_directory();
	if (!shell->directory)
		return (-1);
	return (0);
}


int	main(int argc, char *argv[], char **env)
{
	t_shell	shell;

	init_shell(&shell, env);
	argv = &argv[1];
	cd_command(&shell, argv);
}
