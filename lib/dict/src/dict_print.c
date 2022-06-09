/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:17:42 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/09 02:21:50 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dict.h"
#include "ft_printf.h"

void	dict_print(t_dict *dict, char *prompt)
{
	if (!dict)
		return ;
	while (dict)
	{
		if (str)
			ft_printf("%s%s=%s\n", prompt, dict->key, dict->value);
		else
			ft_printf("%s=%s\n", dict->key, dict->value);
		dict = dict->next;
	}
}
