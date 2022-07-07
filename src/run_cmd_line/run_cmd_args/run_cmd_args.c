/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 02:40:41 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/07 02:54:05 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft.h"
#include "minishell.h"

static int	manage_execve_error(void)
{
	perror(NULL);
	return (-1);
}

static int	execute_child(t_tree *cmd_line, t_shell *shell)
{
	t_node	*content;

	if (manage_redirections(cmd_line) == -1)
		exit(-1);
	content = (t_node *)cmd_line->content;
	if (set_cmd_path(shell, content->args) == -1)
		exit(-1);
	if (execve(content->args[0], content->args, shell->env_str) == -1)
		exit(manage_execve_error());
	exit(0);
}

static int	run_executable(t_tree *cmd_line, t_shell *shell)
{
	pid_t	pid;
	int		ret_value;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		execute_child(cmd_line, shell);
	waitpid(pid, &ret_value, 0);
	return (ret_value);
}

int	run_cmd_args(t_tree *cmd_line, t_shell *shell)
{
	t_node	*content;

	content = (t_node *)cmd_line->content;
	content->args = input_modification(content->args, shell);
	if (!content->args)
		return (-1);
	if (get_my_builtin(content->args[0]) != -1)
		return (run_builtin(shell, cmd_line));
	return (run_executable(cmd_line, shell));
}
