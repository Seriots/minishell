/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 08:39:43 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/10 19:04:54 by rgarrigo         ###   ########.fr       */
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

static int	*get_pid(int nb_sub_commands)
{
	int	*pid;
	int	i;

	pid = malloc(sizeof(int) * (nb_sub_commands + 1));
	if (!pid)
		return (NULL);
	i = 0;
	while (i < nb_sub_commands + 1)
	{
		pid[i] = 0;
		i++;
	}
	return (pid);
}

int	run_pipe_commands(t_tree *commands, t_shell *shell)
{
	t_list	*sub_commands;
	int		nb_sub_commands;
	int		*pid;
	int		wstatus;

	sub_commands = commands->childs;
	nb_sub_commands = list_size(sub_commands);
	pid = get_pid(nb_sub_commands);
	if (!pid)
		return (-1);
	if (fork_and_run_sub_commands(sub_commands, shell, pid) == -1)
	{
		free(pid);
		return (-1);
	}
	waitpid(pid[0], &wstatus, 0);
	wait_sub_commands(pid, nb_sub_commands);
	free(pid);
	if (!WIFEXITED(wstatus))
		return (-1);
	return (WEXITSTATUS(wstatus));
}
