/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_run_sub_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 18:37:27 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/10 20:55:15 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "libft.h"
#include "list.h"
#include "minishell.h"
#include "tree.h"

static void	kill_them_all(int *pid)
{
	int	i;

	i = 0;
	while (pid[i])
	{
		if (kill(pid[i], SIGKILL) == -1)
			ft_putstr_fd("Error: Failed to kill a sub_process\n", 2);
		i++;
	}
}

static void	run_piped_sub_commands(t_tree *commands, t_shell *shell,
	t_pipes *pipes)
{
	int	return_value;

	return_value = 0;
	if (pipes->back[0] != 0 || pipes->back[1] != 0)
	{
		close(pipes->back[1]);
		return_value = dup2(pipes->back[0], 0);
		close(pipes->back[0]);
	}
	if (pipes->front[0] != 0 || pipes->front[1] != 0)
	{
		close(pipes->front[0]);
		if (return_value != -1)
			return_value = dup2(pipes->front[1], 1);
		close(pipes->front[1]);
	}
	if (return_value == -1)
		exit(-1);
	return_value = run_tree_commands(commands, shell);
	exit(return_value);
}

static int	fork_and_run_one_command(t_tree *sub_command, t_shell *shell,
	t_pipes *pipes, int *pid)
{
	int	pid_child;

	pipes->back[0] = pipes->front[0];
	pipes->back[1] = pipes->front[1];
	if (pipe(pipes->front) == -1)
		return (-1);
	pid_child = fork();
	if (pid_child == -1)
	{
		kill_them_all(pid);
		return (-1);
	}
	if (pid_child == 0)
		run_piped_sub_commands(sub_command, shell, pipes);
	close(pipes->back[0]);
	close(pipes->back[1]);
	return (pid_child);
}

static int	fork_and_run_first_subcommand(t_tree *sub_command, t_shell *shell,
	t_pipes *pipes, int *pid)
{
	int	pid_child;

	pipes->back[0] = 0;
	pipes->back[1] = 0;
	if (pipe(pipes->front) == -1)
		return (-1);
	pid_child = fork();
	if (pid_child == -1)
	{
		kill_them_all(pid);
		return (-1);
	}
	if (pid_child == 0)
		run_piped_sub_commands(sub_command, shell, pipes);
	return (pid_child);
}

static int	fork_and_run_last_subcommand(t_tree *sub_command, t_shell *shell,
	t_pipes *pipes, int *pid)
{
	int	pid_child;

	pipes->back[0] = pipes->front[0];
	pipes->back[1] = pipes->front[1];
	pipes->front[0] = 0;
	pipes->front[1] = 0;
	pid_child = fork();
	if (pid_child == -1)
	{
		kill_them_all(pid);
		return (-1);
	}
	if (pid_child == 0)
		run_piped_sub_commands(sub_command, shell, pipes);
	close(pipes->back[0]);
	close(pipes->back[1]);
	return (pid_child);
}

int	fork_and_run_sub_commands(t_list *sub_commands, t_shell *shell,
	int *pid)
{
	int		pipe_back[2];
	int		pipe_front[2];
	t_pipes	pipes;
	int		i;

	pipes.back = pipe_back;
	pipes.front = pipe_front;
	pid[0] = fork_and_run_first_subcommand(sub_commands->content, shell,
			&pipes, pid);
	i = 1;
	while (sub_commands && sub_commands->next)
	{
		pid[i] = fork_and_run_one_command(sub_commands->content, shell, &pipes,
				pid);
		i++;
		sub_commands = sub_commands->next;
	}
	pid[i] = fork_and_run_last_subcommand(sub_commands->content, shell, &pipes,
			pid);
	return (0);
}
