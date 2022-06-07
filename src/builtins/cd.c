/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:18:54 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/07 18:48:31 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../../include/minishell.h"

/*
* cd builtin command, change the current directory to current_directory/path
* on error, return -1 and set errno.
*/

int	cd_command(char *path, int argc, t_shell *shell)
{
	int		error;
	char	*error_message;

	if (argc != 1)
	{
		printf("cd: too many arguments\n");
		return (-1);
	}
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
	if (!shell->directory)
		return (-1);
	printf("%s\n", shell->directory);
	return (0);
}


int	main(int argc, char *argv[], char **env)
{
	t_shell	shell;
	char	buf[100];
	int 	i;
	int		fd;

	if (argc == 1)
		return (0);
	i = 0;
	init_shell(&shell, env);
	cd_command(argv[i + 1], argc - 1, &shell);
}