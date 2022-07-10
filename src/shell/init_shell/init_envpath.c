/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envpath.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 23:36:28 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/09 22:11:07 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "dict.h"
#include "libft.h"
#include "shell.h"

int	add_envpath(t_dict **env, int *error)
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
