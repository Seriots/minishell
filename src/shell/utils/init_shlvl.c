/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shlvl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 23:34:49 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/04 23:35:16 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/dict.h"
#include "../../../include/libft.h"
#include "../../../include/ft_printf.h"
#include "../../../include/minishell.h"
#include <stdlib.h>

int	add_shlvl(t_dict **env, int *error)
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

int	update_shlvl(t_dict **search, int *error)
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
