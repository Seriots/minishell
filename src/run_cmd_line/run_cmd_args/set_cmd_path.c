/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 10:17:42 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/12 03:21:55 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "libft.h"
#include "run_cmd_line.h"
#include "shell.h"

static int	is_dir(char *pathfile)
{
	struct stat	pathfile_info;

	stat(pathfile, &pathfile_info);
	return (S_ISDIR(pathfile_info.st_mode));
}

static void	manage_error_is_a_directory(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	return ;
}

static void	manage_error_access(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	perror(NULL);
	return ;
}

int	set_cmd_path(t_shell *shell, char **cmd)
{
	if (!access(*cmd, F_OK) && !access(*cmd, X_OK))
	{
		if (is_dir(*cmd))
			return (manage_error_is_a_directory(*cmd), 126);
		return (0);
	}
	if (!access(*cmd, F_OK) && access(*cmd, X_OK))
		return (manage_error_access(*cmd), 126);
	return (check_in_path(dict_getelem_key(shell->env, "PATH"), cmd));
}
