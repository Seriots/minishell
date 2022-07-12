/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:58:11 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/12 16:15:02 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "dict.h"
#include "libft.h"
#include "shell.h"

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
		return (NULL);
	ft_strlcpy(result, str, ft_strlen(str) + 1);
	return (result);
}

int	change_oldpwd(t_dict *oldpwd, t_dict *pwd, t_shell **shell)
{
	char	*new_key;

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
		new_key = ft_malloc_str("OLDPWD");
		if (!new_key)
			return (1);
		oldpwd = dict_new(new_key, pwd->value);
		if (!oldpwd)
			return (1);
		dict_add_back(&(*shell)->env, oldpwd, free, free);
	}
	return (0);
}

int	update_pwd(t_shell **shell, char *path)
{
	t_dict	*pwd;
	t_dict	*oldpwd;
	char	*new_path;
	size_t	size;
	int		error;

	pwd = dict_getelem_key((*shell)->env, "PWD");
	oldpwd = dict_getelem_key((*shell)->env, "OLDPWD");
	if (!pwd)
		return (1);
	error = change_oldpwd(oldpwd, pwd, shell);
	if (error)
		return (error);
	size = ft_strlen(path);
	new_path = ft_calloc(sizeof(char), size + 1);
	if (!new_path)
		return (1);
	ft_strlcpy(new_path, path, size + 1);
	pwd->value = new_path;
	return (0);
}
