/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirections_builtin.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:39:30 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/10 21:47:02 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "run_cmd_line.h"
#include "shell.h"
#include "tree.h"

static int	manage_redir_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	perror(": ");
	return (1);
}

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

int	manage_redirections_builtin(t_shell *shell, int fd_backup[3],
	t_tree *cmd_line)
{
	char	*redir_error;

	(void)shell;
	redir_error = 0;
	fd_backup[0] = dup(0);
	fd_backup[1] = dup(1);
	fd_backup[2] = dup(2);
	if (manage_redirections(cmd_line, &redir_error) == -1)
	{
		manage_redir_error(redir_error);
		return (backup_redirections(fd_backup), -1);
	}
	return (0);
}
