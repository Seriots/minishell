/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 23:23:26 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/04 23:23:28 by lgiband          ###   ########.fr       */
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

void	echo_checker(int argc, char *argv[], char **env)
{
	char	**args;
	char	*command;
	char	*check_error;
	int		fd;

	printf("----------------ECHO----------------\n");
	fd = open("src/builtins/checker/echo_test.txt", O_RDONLY);
	command = get_next_line(fd);
	if (command[ft_strlen(command) - 1] == '\n')
		command[ft_strlen(command) - 1] = 0;
	printf("----'%s'----\n", command);
	args = ft_split(command, ' ');
	while (args)
	{
check_error = get_next_line(fd);
		if (echo_command(0, args) == ft_atoi(check_error))
			printf("Return OK\n");
		else
			printf("Return KO\n");
		free (command);
		ft_free_tab(args);
		free(check_error);
		command = get_next_line(fd);
		if (command && command[ft_strlen(command) - 1] == '\n')
			command[ft_strlen(command) - 1] = 0;
		printf("----'%s'----\n", command);
		args = ft_split(command, ' ');
	}
}
