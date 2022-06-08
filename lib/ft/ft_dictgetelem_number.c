/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dictgetelem_number.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:20:46 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/08 19:48:20 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dict	*ft_dictgetelem_number(t_dict *dict, size_t n)
{
	size_t	i;

	if (!dict)
		return (0);
	dict = ft_dictget_first(dict);
	i = 0;
	while (i < n && dict)
	{
		dict = dict->next;
		i ++;
	}
	return (dict);
}
