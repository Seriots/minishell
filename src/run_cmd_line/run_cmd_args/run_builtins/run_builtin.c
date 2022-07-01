/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 12:21:31 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/01 13:08:05 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/tree.h"
#include "../../../../include/minishell.h"
#include "../../../../include/libft.h"

int	manage_redirections_builtin(int fd_backup[3], t_tree *cmd_line)
{
	(void)fd_backup;
	(void)cmd_line;
	return (0);
}

int	backup_redirections(int fd_backup[3])
{
	(void)fd_backup;
	return (0);
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
	int	num_builtin;
	int	ret_value;

	if (!cmd)
		return (-1);
	cmd = input_modification(cmd, shell);
	if (!cmd)
		return (-1);
	num_builtin = get_my_builtin(cmd[0]);
	if (num_builtin < 0)
		return (num_builtin);
	ret_value = shell->builtins[num_builtin](shell, cmd);	
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

	ret_value = manage_redirections_builtin(fd_backup, cmd_line);
	if (ret_value)
		return (ret_value);
	ret_value = execute_builtins(shell, cmd_line);
	backup_redirections(fd_backup);
	return (ret_value);
}