/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_variable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 22:50:05 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/16 11:40:19 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/dict.h"
#include "../../../include/libft.h"
#include "../../../include/ft_printf.h"
#include "../../../include/minishell.h"
#include <stdlib.h>

static int	free_and_set_error(char *key, char *value, int *error)
{
	free(key);
	free(value);
	*error -= 1;
	return (0);
}

static int	add_pwd(t_dict **env, int *error)
{
	t_dict	*new;
	char	*key;
	char	*value;

	value = 0;
	key = 0;
	key = ft_calloc(sizeof(char), 4);
	if (!key)
		return (free_and_set_error(key, value, error));
	ft_strlcpy(key, "PWD", 4);
	value = get_current_directory();
	if (!value)
		return (free_and_set_error(key, value, error));
	new = dict_new(key, value);
	if (!new)
		return (free_and_set_error(key, value, error));
	dict_add_back(env, new, free, free);
	return (*error);
}

static int	add_shlvl(t_dict **env, int *error)
{
	t_dict	*new;
	char	*key;
	char	*value;

	value = 0;
	key = 0;
	key = ft_calloc(sizeof(char), 6);
	if (!key)
		return (free_and_set_error(key, value, error));
	ft_strlcpy(key, "SHLVL", 6);
	value = ft_calloc(sizeof(char), 2);
	if (!value)
		return (free_and_set_error(key, value, error));
	ft_strlcpy(value, "1", 2);
	new = dict_new(key, value);
	if (!new)
		return (free_and_set_error(key, value, error));
	dict_add_back(env, new, free, free);
	return (*error);
}

static int	update_shlvl(t_dict **search, int *error)
{
	char	*new_shlvl;

	new_shlvl = ft_itoa(ft_atoi((*search)->value) + 1);
	if (!new_shlvl)
	{
		*error -= 1;
		return (-1);
	}
	free ((*search)->value);
	(*search)->value = new_shlvl;
	return (*error);
}

static int	add_envpath(t_dict **env, int *error)
{
	t_dict	*new;
	char	*key;
	char	*value;

	value = 0;
	key = 0;
	key = ft_calloc(sizeof(char), 2);
	if (!key)
		return (free_and_set_error(key, value, error));
	ft_strlcpy(key, "_", 2);
	value = ft_calloc(sizeof(char), 13);
	if (!value)
		return (free_and_set_error(key, value, error));
	ft_strlcpy(value, "/usr/bin/env", 13);
	new = dict_new(key, value);
	if (!new)
		return (free_and_set_error(key, value, error));
	dict_add_back(env, new, free, free);
	return (*error);
}

static int	add_oldpwd(t_dict **env, int *error)
{
	t_dict	*new;
	char	*key;
	char	*value;

	value = 0;
	key = 0;
	key = ft_calloc(sizeof(char), 7);
	if (!key)
		return (free_and_set_error(key, value, error));
	ft_strlcpy(key, "OLDPWD", 7);
	new = dict_new(key, value);
	if (!new)
		return (free_and_set_error(key, value, error));
	dict_add_back(env, new, free, free);
	return (*error);
}

int	set_default_variable(t_shell **shell)
{
	t_dict	*search;
	int		error;
	t_dict	**env;
	t_dict	**export;

	env = &(*shell)->env;
	export = &(*shell)->export;
	error = 0;
	search = dict_getelem_key(*env, "PWD");
	if (!search)
		add_pwd(env, &error);
	search = dict_getelem_key(*env, "SHLVL");
	if (!search)
		add_shlvl(env, &error);
	else
		update_shlvl(&search, &error);
	search = dict_getelem_key(*env, "_");
	if (!search)
		add_envpath(env, &error);
	search = dict_getelem_key(*env, "OLDPWD");
	if (!search)
		add_oldpwd(export, &error);
	return (error);
}
