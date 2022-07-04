/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 19:52:51 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/05 00:08:11 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include "libft.h"
#include "list.h"
#include "minishell.h"
#include "run_cmd_line.h"
#include "tree.h"

static void	manage_kill_error(int pid)
{
	ft_putstr_fd("minishell: Failed to kill process ", 2);
	ft_putnbr_fd(pid, 2);
	ft_putstr_fd("\n", 2);
}

static void	kill_them_all(int *pid)
{
	while (*pid != -1)
	{
		if (kill(*pid, SIGTERM) == -1 && kill(*pid, SIGKILL) == -1)
			manage_kill_error(*pid);
		pid++;
	}
}

static int	wait_pipeline(int *pid)
{
	int	ret_value;

	while (*pid)
	{
		waitpid(*pid, &ret_value, 0);
		pid++;
	}
	return (ret_value);
}

int	run_cmd_pipe(t_tree *cmd_line, t_shell *shell)
{
	t_list	*pipeline;
	int		*pid;
	int		ret_value;

	pipeline = cmd_line->childs;
	pid = malloc(sizeof(int) * (list_size(pipeline) + 1));
	if (!pid)
		return (-1);
	ret_value = run_pipeline(pipeline, shell, pid);
	if (ret_value != 0)
		return (kill_them_all(pid), free(pid), ret_value);
	ret_value = wait_pipeline(pid);
	free(pid);
	return (ret_value);
}
