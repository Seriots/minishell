/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dictprint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:17:42 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/08 22:50:21 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dictprint(t_dict *dict, char *str)
{
	if (!dict)
		return ;
	while (dict)
	{
		if (str)
			ft_printf("%s%s=%s\n", str, dict->key, dict->value);
		else
			ft_printf("%s=%s\n", dict->key, dict->value);
		dict = dict->next;
	}
}
