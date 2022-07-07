/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 10:17:42 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/07 15:27:55 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

void	manage_error_access(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(":", 2);
	ft_putstr_fd(" ", 2);
	perror(NULL);
	return ;
}

char	*join_path_and_cmd(char *path, char *cmd)
{
	size_t	size;
	char	*join;

	size = ft_strlen(path) + ft_strlen(cmd);
	if (!(path[ft_strlen(path) - 1] == '/'))
		size ++;
	join = ft_calloc(sizeof(char), size + 1);
	if (!join)
		return (0);
	ft_strlcat(join, path, size + 1);
	if (!(path[ft_strlen(path) - 1] == '/'))
		ft_strlcat(join, "/", size + 1);
	ft_strlcat(join, cmd, size + 1);
	return (join);
}

int	check_each_path(char **all_path, char **cmd)
{
	size_t	i;
	char	*cmd_join;

	i = -1;
	while (++i < ft_arraylen(all_path))
	{
		cmd_join = join_path_and_cmd(all_path[i], *cmd);
		if (!cmd_join)
			return (ft_free_tab(all_path), 1);
		if (!access(cmd_join, F_OK) && !access(cmd_join, X_OK))
		{
			free(*cmd);
			*cmd = cmd_join;
			return (ft_free_tab(all_path), 0);
		}
		if (!access(cmd_join, F_OK) && access(cmd_join, X_OK))
			return (ft_free_tab(all_path), access(cmd_join, X_OK),  127);
		free(cmd_join);
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	return (ft_free_tab(all_path),  127);
}

int	check_in_path(t_dict *path, char **cmd)
{
	char	**all_path;

	if (!path || !path->value)
		return (0);
	all_path = ft_split(path->value, ':');
	if (!all_path)
		return (1);
	return (check_each_path(all_path, cmd));
}

int	set_cmd_path(t_shell *shell, char **cmd)
{
	if (!access(*cmd, F_OK) && !access(*cmd, X_OK))
		return (0);
	if (!access(*cmd, F_OK) && access(*cmd, X_OK))
		return (manage_error_access(*cmd), 126);
	return (check_in_path(dict_getelem_key(shell->env, "PATH"), cmd));
}
