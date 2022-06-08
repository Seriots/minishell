/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dictdelone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:57:41 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/08 18:26:49 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_dictdelone(t_dict **dict, t_dict *elem, int is_malloc)
{
	t_dict	*copy;
	t_dict	*next;
	t_dict	*previous;

	if (!*dict || !elem)
		return ;
	copy = *dict;
	while (copy && copy != elem)
		copy = copy->next;
	if (!copy)
		return ;
	next = copy->next;
	previous = copy->previous;
	if (is_malloc)
	{
		free(copy->key);
		free(copy->value);
	}
	if (previous)
		previous->next = next;
	if (next)
		next->previous = previous;
	if (!copy->previous)
		*dict = ft_dictget_first(copy->next);
	free(copy);
}
