/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:01:20 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/22 13:03:51 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include "../../include/libft.h"
#include "../../include/ft_printf.h"
#include "../../include/list.h"
#include "../../include/minishell.h"

void	insert_wildcard_add(t_list **next, t_list **current,
		t_list **new, t_list **pre)
{
	*next = (*current)->next;
	*pre = list_last(*new);
	list_last(*new)->next = *next;
	list_delone(*current, free);
	*current = *next;
}

char	**list_to_array(t_list *result)
{
	int		nb_elem;
	char	**output;
	int		i;
	t_list	*pre;

	if (!result)
		return (0);
	i = 0;
	nb_elem = list_size(result);
	output = ft_calloc(sizeof(char *), nb_elem + 1);
	if (!output)
		return (0);
	while (result)
	{
		pre = result;
		output[i] = result->content;
		result = result->next;
		free(pre);
		i++;
	}
	return (output);
}

t_wildstr	*init_wildstr(char *str, t_wildstr *wildstr)
{
	wildstr->check_first = 0;
	wildstr->check_last = 0;
	wildstr->split = 0;
	if (!str || ft_strlen(str) == 0)
		return (wildstr);
	if (str[0] != '*')
		wildstr->check_first = 1;
	if (str[ft_strlen(str) - 1] != '*')
		wildstr->check_last = 1;
	return (wildstr);
}

int	is_addable(char *d_name, t_wildstr *split)
{
	size_t		pos_array;
	size_t		pos;
	size_t		is_ok;

	if (!ft_arraylen(split->split))
		return (1);
	pos_array = 0;
	pos = 0;
	if (split->check_first)
	{
		is_ok = check_first_part(d_name, split->split[0], &pos, &pos_array);
		if (is_ok)
			return (1);
	}
	is_ok = check_middle_part(d_name, split, &pos, &pos_array);
	if (is_ok)
		return (1);
	if (split->check_last)
	{
		is_ok = check_last_part(d_name,
				split->split[ft_arraylen(split->split) - 1], &pos, &pos_array);
		if (is_ok)
			return (1);
	}
	return (0);
}
