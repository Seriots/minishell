/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dictadd_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:14:46 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/08 19:48:00 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_dictmodify(t_dict *elem, t_dict *new, int is_malloc)
{
	t_dict	*next;
	t_dict	*previous;

	next = elem->next;
	previous = elem->previous;
	new->next = next;
	new->previous = previous;
	if (next)
		next->previous = new;
	if (previous)
		previous->next = new;
	if (is_malloc)
	{
		free(elem->key);
		free(elem->value);
	}
	free(elem);
}

void	ft_dictadd_front(t_dict **dict, t_dict *new, int is_malloc)
{
	t_dict	*search;

	if (!dict || !new)
		return ;
	if (*dict == 0)
	{
		*dict = new;
		return ;
	}
	*dict = ft_dictget_first(*dict);
	search = ft_dictgetelem_key(*dict, new->key);
	if (!search)
	{
		(*dict)->previous = new;
		new->next = *dict;
		*dict = new;
	}
	else
	{
		if (search->previous == 0)
			*dict = new;
		ft_dictmodify(search, new, is_malloc);
	}
}
