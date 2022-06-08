/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dictclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:13:45 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/08 20:35:58 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_dictclear(t_dict *dict, void free_key(void *),  void free_value(void *))
{
	if (!dict)
		return ;
	while (dict)
	{
		if (free_key)
			free(elem->key);
		if (free_value)
			free(elem->value);
		if (dict->next == 0)
		{
			free(dict);
			dict = 0;
		}
		else
			dict = dict->next;
		if (dict)
			free(dict->previous);
	}
}
