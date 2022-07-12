/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 02:40:41 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/12 19:17:56 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft.h"
#include "run_cmd_line.h"
#include "shell.h"
#include "signals.h"

#include <stdio.h>
static int	manage_execve_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(":", 2);
	ft_putstr_fd(" ", 2);
	perror(NULL);
	return (126);
}

static int	manage_redir_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(":", 2);
	ft_putstr_fd(" ", 2);
	perror(NULL);
	free(cmd);
	return (1);
}

static void	execute_child(t_tree *cmd_line, char **args, t_shell *shell)
{
	char				*redir_error;
	struct sigaction	sig_in_child;

	sig_in_child = init_sigact_child();
	sigaction(SIGINT, &sig_in_child, 0);
	sigaction(SIGQUIT, &sig_in_child, 0);
	redir_error = 0;
	if (manage_redirections(cmd_line, &redir_error) == -1)
		exit(manage_redir_error(redir_error));
	if (execve(args[0], args, shell->env_str) == -1)
		exit(manage_execve_error(args[0]));
}

static int	run_executable(t_tree *cmd_line, t_shell *shell)
{
	t_node	*content;
	pid_t	pid;
	int		ret_value;

	content = (t_node *)cmd_line->content;
	ret_value = set_cmd_path(shell, content->args);
	if (ret_value != 0)
		return (ret_value);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		execute_child(cmd_line, content->args, shell);
	waitpid(pid, &ret_value, 0);
	if (WCOREDUMP(ret_value))
		ft_putstr_fd("Quit (core dumped)\n", 2);
	if (WIFEXITED(ret_value))
		ret_value = WEXITSTATUS(ret_value);
	else if (WIFSIGNALED(ret_value))
		ret_value = WTERMSIG(ret_value) + 128;
	else if (WIFSTOPPED(ret_value))
		ret_value = WSTOPSIG(ret_value) + 128;
	return (ret_value);
}

int	run_cmd_args(t_tree *cmd_line, t_shell *shell)
{
	t_node	*content;

	content = (t_node *)cmd_line->content;
	if (ft_arraylen(content->args) == 0)
		return (0);
	content->args = input_modification(content->args, shell);
	if (!content->args)
		return (-1);
	if (get_my_builtin(content->args[0]) != -1)
		return (run_builtin(shell, cmd_line));
	return (run_executable(cmd_line, shell));
}
