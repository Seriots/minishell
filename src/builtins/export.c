/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:49:17 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/10 21:24:25 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "builtins.h"
#include "dict.h"
#include "libft.h"
#include "shell.h"

/*
* Export builtins command, type export -> show all env variable
* 					type export name=value -> define an env variable
*					type export name+=value -> concatene name variable with value
* If any character other than letters, digit or underscore is use for the name, 
* export of that argument fail and return an error.
*/
static int	add_to_export(t_shell *shell, char *copy, t_dict *new, char *arg)
{
	copy = ft_calloc(sizeof(char), ft_strlen(arg) + 1);
	if (!copy)
		return (1);
	ft_strlcpy(copy, arg, ft_strlen(arg) + 1);
	new = dict_new(copy, 0);
	if (!new)
	{
		free (copy);
		return (1);
	}
	dict_add_back(&shell->export, new, free, free);
	return (0);
}

static int	treat_export(t_shell *shell, char *arg)
{
	t_dict	*new;
	char	*copy;
	t_dict	*search;

	copy = 0;
	new = 0;
	if (check_value(arg))
	{
		new = getarg_env(arg);
		if (!new)
			return (1);
		search = dict_getelem_key(shell->export, new->key);
		if (search)
			dict_delone(&shell->export, search, free, free);
		dict_add_back(&shell->env, new, free, free);
		return (0);
	}
	search = dict_getelem_key(shell->env, arg);
	if (search)
		return (0);
	return (add_to_export(shell, copy, new, arg));
}

static int	concat_input(t_shell *shell, char *key, char *value, t_dict *search)
{
	t_dict	*new;

	if (search)
	{
		free (key);
		key = ft_strjoin(search->value, value);
		free (search->value);
		free (value);
		search->value = key;
	}
	else
	{
		new = dict_new(key, value);
		if (!new)
		{
			free (key);
			free (value);
			return (1);
		}
		dict_add_back(&shell->env, new, free, free);
		search = dict_getelem_key(shell->export, new->key);
		if (search)
			dict_delone(&shell->export, search, free, free);
	}
	return (0);
}

static int	treat_export_concat(t_shell *shell, char *arg)
{
	t_dict	*search;
	size_t	i;
	char	*key;
	char	*value;

	i = 0;
	while (arg[i] != '+')
		i++;
	key = ft_substr(arg, 0, i);
	if (!key)
		return (1);
	value = ft_substr(arg, i + 2, ft_strlen(arg) - i - 2);
	if (!value)
	{
		free (key);
		return (1);
	}
	search = dict_getelem_key(shell->env, key);
	return (concat_input(shell, key, value, search));
}

int	export_command(t_shell *shell, char **arguments)
{
	size_t	i;
	int		is_concat;
	int		error;
	int		return_error;

	i = 0;
	error = 0;
	return_error = 0;
	if (ft_arraylen(arguments) == 0)
		return (print_export(shell));
	while (arguments[i])
	{
		is_concat = check_key(arguments[i]);
		if (is_concat == 1)
			error = treat_export(shell, arguments[i]);
		else if (is_concat == 2)
			error = treat_export_concat(shell, arguments[i]);
		else
			error = invalid_identifier_export(arguments[i]);
		if (return_error == 0)
			return_error = error;
		i++;
	}
	return (return_error);
}
