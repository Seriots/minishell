/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 23:23:10 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/04 23:23:12 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/libft.h"
#include "../../../include/get_next_line.h"
#include "../../../include/minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void	cd_checker(int argc, char *argv[], char **env)
{
	t_shell	shell;
	char	**args;
	char	*command;
	char	*check_error;
	int		fd;

	printf("----------------CD----------------\n");
	init_shell(&shell, env);
	fd = open("src/builtins/checker/cd_test.txt", O_RDONLY);
	command = get_next_line(fd);
	if (command[ft_strlen(command) - 1] == '\n')
		command[ft_strlen(command) - 1] = 0;
	printf("----'%s'----\n", command);
	args = ft_split(command, ' ');
	while (args)
	{
		printf("-<%s\n", shell.directory);
		check_error = get_next_line(fd);
		if (cd_command(&shell, args) == ft_atoi(check_error))
			printf("Return OK\n");
		else
			printf("Return KO\n");
		printf("->%s\n", shell.directory);
		free (command);
		free(check_error);
		ft_free_tab(args);
		command = get_next_line(fd);
		if (command && command[ft_strlen(command) - 1] == '\n')
			command[ft_strlen(command) - 1] = 0;
		printf("----'%s'----\n", command);
		args = ft_split(command, ' ');
	}
	free_shell(&shell);
}
