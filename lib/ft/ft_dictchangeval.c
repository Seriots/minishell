/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dictchangeval.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:34:00 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/08 20:32:59 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_dictchangeval(t_dict **dict, void *key, void *value, void free_value(void *))
{
	t_dict	*elem;

	if (!dict || !key || !value)
		return ;
	elem = ft_dictgetelem_key(*dict, key);
	if (!elem)
		return ;
	if (free_value)
		free_value(elem->value);
	elem->value = value;
}
