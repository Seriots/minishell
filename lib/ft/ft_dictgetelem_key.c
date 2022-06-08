/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dictgetelem_key.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:29:00 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/08 18:35:06 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dict	*ft_dictgetelem_key(t_dict *dict, void *key)
{
	if (!dict || !key)
		return (0);
	dict = ft_dictget_first(dict);
	while (dict && ft_strncmp(dict->key, key, ft_strlen(key) + 1) != 0)
		dict = dict->next;
	return (dict);
}
