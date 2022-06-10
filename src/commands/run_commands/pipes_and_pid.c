/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_and_pid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 08:53:47 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/10 11:19:10 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "list.h"
#include "minishell.h"
#include "tree.h"

static int	init_pid(int **pid, int nb_sub_commands)
{
	int	i;

	*pid = malloc(sizeof(int) * nb_sub_commands);
	if (!*pid)
		return (-1);
	i = 0;
	while (i < nb_sub_commands)
	{
		(*pid)[i] = 0;
		i++;
	}
	return (0);
}

static int	init_pipes(int ***pipe_fd, int nb_sub_commands)
{
	int	i;

	*pipe_fd = malloc(sizeof(int *) * (nb_sub_commands + 1));
	if (!*pipe_fd)
		return (-1);
	i = 0;
	while (i < nb_sub_commands + 1)
	{
		(*pipe)[i] = 0;
		i++;
	}
	i = 0;
	while (i < nb_sub_commands)
	{
		(*pipe)[i] = malloc(sizeof(int) * 2);
		if (!(*pipe)[i])
			return (-1);
		(*pipe)[i][0] = 0;
		(*pipe)[i][1] = 0;
		if (pipe2((*pipe)[i], 0) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	init_pipes_and_pids(int ***pipe_fd, int **pid, int nb_sub_commands)
{
	if (init_pid(pid, nb_sub_commands) == -1)
		return (-1);
	if (init_pipes(pipe_fd, nb_sub_commands) == -1)
	{
		free_pipes_and_pids(pipe_fd, pid, nb_sub_commands);
		return (-1);
	}
	return (0);
}

void	free_pipes_and_pids(int **pipe_fd, int *pid, int nb_sub_commands)
{
	int	i;

	i = -1;
	while (++i < nb_sub_commands)
	{
		if (!pipe_fd[i])
			continue ;
		if (pipe_fd[i][0])
			close(pipe_fd[i][0]);
		if (pipe_fd[i][1])
			close(pipe_fd[i][1]);
		free(pipe_fd[i]);
	}
	free(pipe_fd);
	free(pid);
}
