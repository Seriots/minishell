/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:49:48 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/10 17:51:51 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/dict.h"
#include "../../../include/libft.h"
#include "../../../include/ft_printf.h"
#include "../../../include/minishell.h"
#include <stdlib.h>

int	init_export_copy(t_shell *shell, t_dict **copy,
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

int	print_export(t_shell *shell)
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
	return (0);
}

int	invalid_identifier(char *arg)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (-1);
}

int	check_key(char *arg)
{
	size_t	i;

	i = 0;
	if (!arg)
		return (0);
	while (arg[i] && arg[i] != '=' && arg[i] != '+')
	{
		if (!ft_isalnum(arg[i]) && !(arg[i] == '_'))
			return (0);
		i++;
	}
	if (i == 0)
		return (0);
	if (arg[i] == '+' && arg[i + 1] != '=')
		return (0);
	if (arg[i] == '+')
		return (2);
	else
		return (1);
}

int	check_value(char *arg)
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
