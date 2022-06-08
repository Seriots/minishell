/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dictprint_values.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:44:57 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/08 19:45:08 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dictprint_values(t_dict *dict)
{
	if (!dict)
		return ;
	while (dict)
	{
		ft_printf("%s\n", dict->value);
		dict = dict->next;
	}
}
