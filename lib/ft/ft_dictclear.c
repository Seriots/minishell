/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dictclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:13:45 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/07 20:18:49 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
void	ft_dictclear(t_dict *dict)
{
	if (!dict)
		return ;
	while (dict)
	{
		free(dict->key);
		free(dict->value);
		if (dict->next == 0)
			free(dict);
		dict = dict->next;
		if (dict)
			free(dict->previous);
	}
}
