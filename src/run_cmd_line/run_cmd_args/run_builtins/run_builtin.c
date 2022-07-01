/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 12:21:31 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/01 14:44:42 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/tree.h"
#include "../../../../include/minishell.h"
#include "../../../../include/libft.h"
#include "../../../../include/dict.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int	manage_redirections_builtin(t_shell *shell, int fd_backup[3], t_tree *cmd_line)
{
	/*
	* C'ets qu'un test j'ai pas compris le fonctionnent de t_redirs, 
	* mais avec les test que j'ai fait je me demande si on doit pas
	* faire un join avec pwd pour l'open du fichier creer voila voila
	* 
	*/
	int	fd_stdout;

	(void)cmd_line;
	fd_backup[0] = dup(0);
	fd_backup[1] = dup(1);
	fd_backup[2] = dup(2);
	
	fd_stdout = open(ft_strjoin(dict_getelem_key(shell->env, "PWD")->value, "/coucou"), O_RDWR | O_CREAT);
	printf("fd = %d\n", fd_stdout);
	if (fd_stdout != -1)
		dup2 (fd_stdout, 1);
	return (0);
}

int	backup_redirections(int fd_backup[3])
{
	int ret_value;
	
	ret_value = dup2(fd_backup[0], 0);
	if (ret_value != -1)
		ret_value = dup2(fd_backup[1], 1);
	if (ret_value != -1)
		ret_value = dup2(fd_backup[2], 2);
	return (ret_value);
}

int	get_my_builtin(char *name)
{
	if (!ft_strncmp(name, "cd", ft_strlen(name) + 1))
		return (0);
	else if (!ft_strncmp(name, "echo", ft_strlen(name) + 1))
		return (1);
	else if (!ft_strncmp(name, "env", ft_strlen(name) + 1))
		return (2);
	else if (!ft_strncmp(name, "exit", ft_strlen(name) + 1))
		return (3);
	else if (!ft_strncmp(name, "export", ft_strlen(name) + 1))
		return (4);
	else if (!ft_strncmp(name, "pwd", ft_strlen(name) + 1))
		return (5);
	else if (!ft_strncmp(name, "unset", ft_strlen(name) + 1))
		return (6);
	return (-1);
}

int	execute_builtin(t_shell *shell, char **cmd)
{
	int		num_builtin;
	int		ret_value;

	if (!cmd)
		return (-1);
	num_builtin = get_my_builtin(cmd[0]);
	if (num_builtin < 0)
		return (ft_free_tab(cmd), num_builtin);
	ret_value = shell->builtins[num_builtin](shell, &cmd[1]);	
	ft_free_tab(cmd);
	return (ret_value);
}

int	execute_builtins(t_shell *shell, t_tree *cmd)
{
	t_node	*content;
	int		return_value;

	if (!cmd || !cmd->content)
		return (-1);
	content = (t_node *)cmd->content;
	return_value = execute_builtin(shell, content->args);
	return (return_value);
}

int	run_builtin(t_shell *shell, t_tree *cmd_line)
{
	int	fd_backup[3];
	int	ret_value;

	ret_value = manage_redirections_builtin(shell, fd_backup, cmd_line);
	if (ret_value)
		return (ret_value);
	ret_value = execute_builtins(shell, cmd_line);
	backup_redirections(fd_backup);
	return (ret_value);
}

int	main(int argc, char *argv[], char **env)
{
	t_shell shell;
	char	**copy;
	int		ret_value;

	init_shell(&shell, env);
	copy = ft_calloc(sizeof(char *), argc);
	if (!copy)
		return (0);
	for (int i = 0; i < argc - 1; i++)
		copy[i] = ft_strdup(argv[i + 1]);
	//ret_value = run_builtin(&shell, copy);
	free_shell(&shell);
}