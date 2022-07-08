/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 02:40:41 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/08 11:43:31 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft.h"
#include "minishell.h"

extern int	g_stop_run;

static int	manage_execve_error(void)
{
	perror(NULL);
	return (1);
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

static int	execute_child(t_tree *cmd_line, t_shell *shell)
{
	t_node	*content;
	char	*redir_error;
	int		ret_value;

	redir_error = 0;
	if (manage_redirections(cmd_line, &redir_error) == -1)
		exit(manage_redir_error(redir_error));
	content = (t_node *)cmd_line->content;
	ret_value = set_cmd_path(shell, content->args);
	if (ret_value != 0)
		exit(ret_value);
	if (execve(content->args[0], content->args, shell->env_str) == -1)
		exit(manage_execve_error());
	exit(0);
}

static int	run_executable(t_tree *cmd_line, t_shell *shell)
{
	pid_t				pid;
	int					ret_value;
	struct sigaction	sig_in_child;
	struct sigaction	sig_reset;

	sig_in_child = init_sigact_child();
	sig_reset = init_sigact();
	ret_value = -2;
	sigaction(SIGINT, &sig_in_child, 0);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		execute_child(cmd_line, shell);
	while (ret_value == -2)
		waitpid(pid, &ret_value, 0);
	sigaction(SIGINT, &sig_reset, 0);
	ret_value = WEXITSTATUS(ret_value);
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
