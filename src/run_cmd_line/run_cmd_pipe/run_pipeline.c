/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 20:39:21 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/01 04:20:47 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "list.h"
#include "minishell.h"
#include "run_cmd_line.h"

static void	init_pipes(int pipes[2][2])
{
	pipes[1][0] = -1;
	pipes[1][1] = -1;
}

static int	set_pipes(int pipes[2][2], void *next)
{
	pipes[0][0] = pipes[1][0];
	pipes[0][1] = pipes[1][1];
	if (next == NULL)
	{
		pipes[1][0] = -1;
		pipes[1][1] = -1;
		return (0);
	}
	return (pipe(pipes[1]));
}

static void	close_pipe(int *pipe_fd)
{
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
}

static int	run_piped_subshell(t_tree *cmd_subshell, t_shell *shell,
	int pipes[2][2])
{
	int	pid;
	int	ret_value;

	pid = fork();
	if (pid == 0)
	{
		if (pipes[0][1] != -1 && dup2(0, pipes[0][1]) == -1)
		{
			close_pipe(pipes[0]);
			close_pipe(pipes[1]);
			exit(-1);
		}
		close_pipe(pipes[0]);
		if (pipes[1][0] != -1 && dup2(1, pipes[1][0]) == -1)
		{
			close_pipe(pipes[1]);
			exit(-1);
		}
		close_pipe(pipes[1]);
		ret_value = run_cmd_line(cmd_subshell, shell);
		exit(ret_value);
	}
	return (pid);
}

int	run_pipeline(t_list *pipeline, t_shell *shell, int *pid)
{
	int		pipes[2][2];

	init_pipes(pipes);
	while (pipeline)
	{
		if (set_pipes(pipes, pipeline->next) == -1)
			return (close_pipe(pipes[0]), -1);
		*pid = run_piped_subshell(pipeline->content, shell, pipes);
		close_pipe(pipes[0]);
		if (*pid == -1)
			return (close_pipe(pipes[1]), -1);
		pid++;
		pipeline = pipeline->next;
	}
	*pid = 0;
	return (0);
}
