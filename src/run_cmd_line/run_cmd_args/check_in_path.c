/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 03:17:14 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/12 03:22:04 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "dict.h"
#include "libft.h"

static char	*join_path_and_cmd(char *path, char *cmd)
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

static void	manage_error_command_not_found(char **cmd, char **all_path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	ft_free_tab(all_path);
}

static int	check_each_path(char **all_path, char **cmd)
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
			return (ft_free_tab(all_path), access(cmd_join, X_OK), 127);
		free(cmd_join);
	}
	return (manage_error_command_not_found(cmd, all_path), 127);
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
