/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 02:40:41 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/06 10:02:11 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/libft.h"
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int	execute_parent(pid_t pid)
{
	int	ret_value;

	waitpid(pid, &ret_value, 0);
	return (ret_value);
}

int	manage_execve_error(void)
{
	return (-1);
}

int	execute_child(t_tree *cmd_line, t_shell *shell)
{
	t_node	*content;

	if (manage_redirections(cmd_line) == -1)
		return (-1);
	content = (t_node *)cmd_line->content;
	if (set_cmd_path(shell, content->args) == -1)
		return (-1);
	return (execve(content->args[0], content->args, shell->env_str));
}

int	run_executable(t_tree *cmd_line, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if (execute_child(cmd_line, shell) == -1)
			exit(manage_execve_error());
		exit(0);
	}
	return (execute_parent(pid));
}

int	run_cmd_args(t_tree *cmd_line, t_shell *shell)
{
	t_node	*content;

	content = (t_node *)cmd_line->content;
	content->args = input_modification(content->args, shell);
	if (get_my_builtin(content->args[0]) != -1)
		return (run_builtin(shell, cmd_line));
	return (run_executable(cmd_line, shell));
}
