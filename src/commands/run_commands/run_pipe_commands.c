/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 08:39:43 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/10 11:14:18 by rgarrigo         ###   ########.fr       */
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

static void	kill_them_all(int *pid, int pid_size)
{
	int	i;

	i = 0;
	while (i < pid_size)
	{
		if (kill(pid[i], SIGKILL) == -1)
			ft_putstr("Error: Failed to kill a sub_process\n");
		i++;
	}
}

static int	run_piped_sub_commands(t_tree *commands, t_shell *shell,
	int **pipe_fd, int i)
{
	int	return_value;

	if (pipe_fd[i])
		dup2(pipe_fd[i][0], 0);
	if (pipe_fd[i + 1])
		dup2(pipe_fd[i][1], 1);
	return_value = run_tree_commands(commands, shell);
	if (pipe_fd[i])
	{
		close(pipe_fd[i][0]);
		pipe_fd[i][0] = 0;
	}
	if (pipe_fd[i + 1])
	{
		close(pipe_fd[i + 1][1]);
		pipe_fd[i + 1][1] = 0;
	}
	exit(return_value);
}

static int	fork_and_run_sub_commands(t_list *sub_commands, t_shell *shell,
	int **pipe_fd, int *pid)
{
	int	pid_child;
	int	i;

	i = 0;
	while (sub_commands)
	{
		pid_child = fork();
		if (pid_child == -1)
		{
			kill_them_all(pid, i);
			return (-1);
		}
		if (pid_child == 0)
			run_piped_sub_commands(sub_commands->content, shell, pipe_fd, i);
		pid[i] = pid_child;
		i++;
		sub_commands = sub_commands->next;
	}
	return (0);
}

static void	wait_sub_commands(int *pid, int nb_sub_commands)
{
	int	i;

	i = 1;
	while (i < nb_sub_commands)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
}

int	run_pipe_commands(t_tree *commands, t_shell *shell)
{
	t_list	*sub_commands;
	int		nb_sub_commands;
	int		**pipe_fd;
	int		*pid;
	int		*wstatus;

	sub_commands = commands->childs;
	nb_sub_commands = list_size(sub_commands);
	if (init_pipes_and_pids(&pipe_fd, &pid, nb_sub_commands) == -1)
		return (-1);
	if (fork_and_run_sub_commands(sub_commands, shell, pipe_fd, pid) == -1)
	{
		free_pipes_and_pids(pipe_fd, pid, nb_sub_commands);
		return (-1);
	}
	waitpid(*pid, wstatus, 0);
	wait_sub_commands(pid, nb_sub_commands);
	free_pipes_and_pids(pipe_fd, pid, nb_sub_commands);
	if (!WIFEXITED(wstatus))
		return (-1);
	return (WEXITSTATUS(wstatus));
}
