/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dictgetelem_value.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:16:08 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/08 19:17:00 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dict	*ft_dictgetelem_value(t_dict *dict, void *value)
{
	if (!dict || !value)
		return (0);
	dict = ft_dictget_first(dict);
	while (dict && ft_strncmp(dict->value, value, ft_strlen(value) + 1) != 0)
		dict = dict->next;
	return (dict);
}