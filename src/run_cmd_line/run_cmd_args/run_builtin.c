/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 12:21:31 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/06 23:08:42 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/tree.h"
#include "../../../include/minishell.h"
#include "../../../include/libft.h"
#include "../../../include/dict.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int	backup_redirections(int fd_backup[3])
{
	if (dup2(fd_backup[0], 0) == -1)
		return (close(fd_backup[0]), close(fd_backup[1]),
			close(fd_backup[2]), -1);
	close(fd_backup[0]);
	if (dup2(fd_backup[1], 1) == -1)
		return (close(fd_backup[1]), close(fd_backup[2]), -1);
	close(fd_backup[1]);
	if (dup2(fd_backup[2], 2) == -1)
		return (close(fd_backup[2]), -1);
	close(fd_backup[2]);
	return (0);
}

/*
* C'ets qu'un test j'ai pas compris le fonctionnent de t_redirs, 
* mais avec les test que j'ai fait je me demande si on doit pas
* faire un join avec pwd pour l'open du fichier creer voila voila
* 
*/
int	manage_redirections_builtin(t_shell *shell, int fd_backup[3],
	t_tree *cmd_line)
{
	(void)shell;
	fd_backup[0] = dup(0);
	fd_backup[1] = dup(1);
	fd_backup[2] = dup(2);
	if (manage_redirections(cmd_line) == -1)
		return (backup_redirections(fd_backup), -1);
	return (0);
}

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
