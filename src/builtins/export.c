/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:49:17 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/09 22:14:55 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/dict.h"
#include "../../include/libft.h"
#include "../../include/ft_printf.h"
#include "../../include/minishell.h"
#include <stdlib.h>

static int	init_export_copy(t_shell *shell, t_dict **copy,
		t_dict **export_copy)
{
	if (shell->env)
	{
		*copy = dict_copy(shell->env);
		if (!*copy)
			return (-1);
	}
	if (shell->export)
	{
		*export_copy = dict_copy(shell->export);
		if (!*export_copy)
		{
			dict_clear(*copy, free, free);
			return (-1);
		}
		dict_append(copy, export_copy);
	}
	dict_sort(copy);
	return (0);
}

static int	print_export(t_shell *shell)
{
	t_dict	*copy;
	t_dict	*export_copy;

	export_copy = 0;
	copy = 0;
	if (init_export_copy(shell, &copy, &export_copy))
		return (-1);
	export_copy = copy;
	while (copy)
	{
		if (ft_strncmp(copy->key, "_", 2))
		{
			if (copy->value)
				ft_printf("declare -x %s=\"%s\"\n", copy->key, copy->value);
			else
				ft_printf("declare -x %s\n", copy->key);
		}
		copy = copy->next;
	}
	copy = dict_get_first(export_copy);
	dict_clear(copy, free, free);
}

static int	check_key(char *arg)
{
	size_t	i;

	i = 0;
	if (!arg)
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && !(arg[i] == '_'))
		{
			ft_printf("export: `%s': not a valid identifier\n", arg);
			return (0);
		}
		i++;
	}
	if (i == 0)
	{
		ft_printf("export: `%s': not a valid identifier\n", arg);
		return (0);
	}
	return (1);
}

static int	check_value(char *arg)
{
	size_t	i;

	i = 0;
	if (!arg)
		return (0);
	while (arg[i] && arg[i] != '=')
		i ++;
	if (!arg[i])
		return (0);
	return (1);
}

static int	treat_export(t_shell *shell, char **arguments, size_t i)
{
	t_dict	*new;
	char	*copy;
	t_dict	*search;

	if (check_value(arguments[i]))
	{
		new = getarg_env(arguments[i]);
		if (!new)
			return (-1);
		search = dict_getelem_key(shell->export, new->key);
		if (search)
			dict_delone(&shell->export, search, free, free);
		dict_add_back(&shell->env, new, free, free);
		return (0);
	}
	copy = ft_calloc(sizeof(char), ft_strlen(arguments[i]) + 1);
	if (!copy)
		return (-1);
	ft_strlcpy(copy, arguments[i], ft_strlen(arguments[i]) + 1);
	new = dict_new(copy, 0);
	if (!new)
		return (-1);
	dict_add_back(&shell->export, new, free, free);
	return (0);
}

int	export_command(t_shell *shell, char **arguments)
{
	size_t	i;

	i = 0;
	if (ft_arraylen(arguments) == 0)
		return (print_export(shell));
	while (arguments[i])
	{
		if (check_key(arguments[i]))
		{
			if (treat_export(shell, arguments, i))
				return (-1);
		}
		i++;
	}
}

int	main(int argc, char *argv[], char **env)
{
	t_shell	shell;

	init_shell(&shell, env);
	argv = &argv[1];
	export_command(&shell, argv);
	print_export(&shell);
	free_shell(&shell);
}
