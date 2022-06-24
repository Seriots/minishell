/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_arguments_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:45:33 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/25 00:13:20 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../../include/minishell.h"
#include "../../../include/libft.h"
#include "../../../include/dict.h"
#include "../../../include/ft_printf.h"

int	oppose_quote(int is_quoted)
{
	if (is_quoted)
		return (0);
	return (1);
}

char	*get_var(char *input, int pos)
{
	char	*var;
	size_t	size;

	size = 0;
	while (ft_is_varchar(input[pos + size]))
		size += 1;
	var = ft_calloc(sizeof(char), size + 1);
	if (!var)
		return (0);
	ft_strlcpy(var, &input[pos], size + 1);
	return (var);
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
	if (ft_isalnum(c))  // || c == '_'
		return (1);
	return (0);
}
