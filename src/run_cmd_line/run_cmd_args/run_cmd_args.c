/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 02:40:41 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/04 14:35:33 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void	manage_child_errors(int ret_value)
{
	(void)ret_value;
}

int	execute_parent(pid_t pid)
{
	int	ret_value;

	ret_value = 0;
	waitpid(pid, &ret_value, 0);
	manage_child_errors(ret_value);
	return (ret_value);
}

int	manage_execve_error(int ret_value)
{
	(void)ret_value;
	return (1);
}

int	execute_child(t_tree *cmd_line, t_shell *shell)
{
	int		ret_value;
	t_node	*content;

	ret_value = 0;
	ret_value = manage_redirections(cmd_line);
	if (ret_value)
		return (ret_value);
	content = (t_node *)cmd_line->content;
	ret_value = set_cmd_path(shell, content->args);
	if (ret_value)
		return (ret_value);
	ret_value = execve(content->args[0], content->args, shell->env_str);
	return (ret_value);
}

int	run_executable(t_tree *cmd_line, t_shell *shell)
{
	pid_t	pid;
	int 	ret_value;
	
	ret_value = 0;
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		ret_value = execute_child(cmd_line, shell);
		if (ret_value == -1)
			exit(manage_execve_error(ret_value));
		exit(0);
	}
	else
		ret_value = execute_parent(pid);
	return (ret_value);
}

int	run_cmd_args(t_tree *cmd_line, t_shell *shell)
{
	t_node	*content;
	int		ret_value;

	content = (t_node *)cmd_line->content;
	content->args = input_modification(content->args, shell);
	if (get_my_builtin(content->args[0]) != -1)
		ret_value = run_builtin(shell, cmd_line);
	else
		ret_value = run_executable(cmd_line, shell);
	free_cmd_line(content);
	return (ret_value);
}

/*
int	main(int argc, char *argv[], char **env)
{
	t_shell shell;
	t_tree	cmd_line;
	t_node	content;
	int	ret_value;
	int	i;

	i = 0;
	content.args = ft_calloc(sizeof(char *), argc);
	while (++i < argc)
		content.args[i - 1] = ft_strdup(argv[i]);
	content.redirs = 0;
	content.tag = 0;
	cmd_line.childs = 0;
	cmd_line.content = &content;
	init_shell(&shell, env);
	ret_value = run_cmd_args(&cmd_line, &shell);
	printf("%d\n", ret_value);
	free_shell(&shell);
}*/