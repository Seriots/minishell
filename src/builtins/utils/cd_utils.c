/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:58:11 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/07 03:06:37 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "dict.h"
#include "libft.h"
#include "minishell.h"

void	print_error_message_cd(char *path)
{
	char	*error_message;

	error_message = ft_strjoin("minishell: cd: ", path);
	perror(error_message);
	free(error_message);
}

char	*ft_malloc_str(const char *str)
{
	char	*result;

	result = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	if (!result)
		return (0);
	ft_strlcpy(result, str, ft_strlen(str) + 1);
	return (result);
}

void	change_oldpwd(t_dict *oldpwd, t_dict *pwd, t_shell **shell)
{
	if (oldpwd)
	{
		free(oldpwd->value);
		oldpwd->value = pwd->value;
	}
	else
	{
		oldpwd = dict_getelem_key((*shell)->export, "OLDPWD");
		if (oldpwd)
			dict_delone(&(*shell)->export, oldpwd, free, free);
		oldpwd = dict_new(ft_malloc_str("OLDPWD"), pwd->value);
		dict_add_back(&(*shell)->env, oldpwd, free, free);
	}
}

int	update_pwd(t_shell **shell, char *path)
{
	t_dict	*pwd;
	t_dict	*oldpwd;
	char	*new_path;
	size_t	size;

	pwd = dict_getelem_key((*shell)->env, "PWD");
	oldpwd = dict_getelem_key((*shell)->env, "OLDPWD");
	if (!pwd)
		return (1);
	change_oldpwd(oldpwd, pwd, shell);
	size = ft_strlen(path);
	new_path = ft_calloc(sizeof(char), size + 1);
	if (!new_path)
		return (1);
	ft_strlcpy(new_path, path, size + 1);
	pwd->value = new_path;
	return (0);
}
