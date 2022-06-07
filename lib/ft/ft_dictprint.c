/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dictprint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:17:42 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/07 19:52:51 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dictprint(t_dict *dict)
{
	if (!dict)
		return ;
	while (dict)
	{
		ft_printf("%s=%s\n", dict->key, dict->value);
		dict = dict->next;
	}
}