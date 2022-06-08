/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dictsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:22:24 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/08 17:36:39 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_dictsize(t_dict *dict)
{
	size_t	i;

	if (!dict)
		return (0);
	i = 0;
	while (dict)
	{
		i++;
		dict = dict->next;
	}
	return (i);
}
