/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 20:39:21 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/13 18:08:34 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "list.h"
#include "shell.h"
#include "run_cmd_line.h"

extern t_shell_status	g_shell_status;

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
		g_shell_status = running_subshell_cmd_line;
		if (pipes[0][0] != -1 && dup2(pipes[0][0], 0) == -1)
		{
			close_pipe(pipes[0]);
			close_pipe(pipes[1]);
			exit(-1);
		}
		close_pipe(pipes[0]);
		if (pipes[1][1] != -1 && dup2(pipes[1][1], 1) == -1)
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
	while ((g_shell_status == running_cmd_line
			|| g_shell_status == running_subshell_cmd_line)
		&& pipeline)
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
	if (g_shell_status == reading_cmd_line)
		return (-1);
	return (0);
}
