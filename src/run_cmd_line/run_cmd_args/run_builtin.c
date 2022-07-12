/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 12:21:31 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/12 22:50:10 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "run_cmd_line.h"
#include "shell.h"
#include "tree.h"

int	get_my_builtin(char *name)
{
	const char	*builtin_name[] = {"cd", "echo", "env", "exit", "export",
		"pwd", "unset"};
	int			i;

	i = 0;
	while (i < 7)
	{
		if (!ft_strncmp(name, builtin_name[i], ft_strlen(name) + 1))
			return (i);
		i++;
	}
	return (-1);
}

int	execute_builtin(t_shell *shell, t_tree *cmd)
{
	char	**args;
	int		num_builtin;

	if (!cmd || !cmd->content)
		return (-1);
	args = ((t_node *) cmd->content)->args;
	if (!args)
		return (-1);
	num_builtin = get_my_builtin(args[0]);
	if (num_builtin < 0)
		return (num_builtin);
	return (shell->builtins[num_builtin](shell, args + 1));
}

int	run_builtin(t_shell *shell, t_tree *cmd_line)
{
	int	fd_backup[3];
	int	ret_value;

	ret_value = manage_redirections_builtin(shell, fd_backup, cmd_line);
	if (ret_value)
		return (ret_value);
	ret_value = execute_builtin(shell, cmd_line);
	backup_redirections(fd_backup);
	return (ret_value);
}
