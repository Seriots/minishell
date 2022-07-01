/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 10:17:42 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/01 12:17:34 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/libft.h"
#include <stdlib.h>
#include <unistd.h>

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
	int		i;
	char	*cmd_join;

	i = -1;
	while (++i < ft_arraylen(all_path))
	{
		cmd_join = join_path_and_cmd(all_path[i], *cmd);
		if (!cmd_join)
			return (ft_free_tab(all_path), -1);
		if (!access(cmd_join, F_OK) && !access(cmd_join, X_OK))
		{
			free(*cmd);
			*cmd = cmd_join;
			return (ft_free_tab(all_path), 0);
		}
		else if (!access(cmd_join, F_OK) && access(cmd_join, X_OK))
			return (ft_free_tab(all_path), access(cmd_join, X_OK));
		else if (i == ft_arraylen(all_path) - 1)
			return (ft_free_tab(all_path), free(cmd_join), -1);
		free(cmd_join);
	}
	return (-1);
}

int	check_in_path(t_dict *path, char **cmd)
{
	char	**all_path;

	if (!path || !path->value)
		return (0);
	all_path = ft_split(path->value, ':');
	if (!all_path)
		return (-1);
	return (check_each_path(all_path, cmd));
}

int	set_cmd_path(t_shell *shell, char **cmd)
{
	int	ret_value;

	if (!access(*cmd, F_OK) && !access(*cmd, X_OK))
		return (0);
	else if (!access(*cmd, F_OK) && access(*cmd, X_OK))
		return (access(*cmd, X_OK));
	else
		return (check_in_path(dict_getelem_key(shell->env, "PATH"), cmd));
}
