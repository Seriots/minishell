/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dictgetfirst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:41:37 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/08 17:56:19 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dict	*ft_dictget_first(t_dict *dict)
{
	if (!dict)
		return (0);
	while (dict->previous != 0)
		dict = dict->previous;
	return (dict);
}
