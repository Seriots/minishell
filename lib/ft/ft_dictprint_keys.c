/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dictprint_keys.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:43:55 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/08 19:44:34 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dictprint_keys(t_dict *dict)
{
	if (!dict)
		return ;
	while (dict)
	{
		ft_printf("%s\n", dict->key);
		dict = dict->next;
	}
}
