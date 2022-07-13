/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_arguments_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:45:33 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/14 00:41:26 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "dict.h"
#include "libft.h"
#include "run_cmd_line.h"

int	update_quote(char last_quote, char quote_seen)
{
	if (last_quote == 0)
		return (quote_seen);
	if (last_quote == quote_seen)
		return (0);
	return (last_quote);
}

int	set_var(char **var, char *input, int pos)
{
	size_t	size;

	size = 0;
	while (ft_is_varchar(input[pos + size]))
		size++;
	*var = ft_calloc(sizeof(char), size + 1);
	if (!*var)
		return (-1);
	ft_strlcpy(*var, &input[pos], size + 1);
	return (0);
}

size_t	get_size_var(char *var, t_dict *env)
{
	t_dict	*search;

	search = dict_getelem_key(env, var);
	if (!search)
		return (0);
	return (ft_strlen(search->value));
}

size_t	concat_var(char *var, t_dict *env, char **result, size_t nb_letters)
{
	t_dict	*search;

	search = dict_getelem_key(env, var);
	if (!search)
		return (0);
	ft_strlcat(*result, search->value,
		nb_letters + ft_strlen(search->value) + 1);
	return (ft_strlen(search->value));
}

int	ft_is_varchar(char c)
{
	if (ft_isalnum(c))
		return (1);
	return (0);
}
