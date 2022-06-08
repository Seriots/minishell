/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dictgetlast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:47:18 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/08 17:56:22 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dict	*ft_dictget_last(t_dict *dict)
{
	if (!dict)
		return (0);
	while (dict->next != 0)
		dict = dict->next;
	return (dict);
}
