/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:01:44 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/02 16:54:31 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

char	*str_buff_join(char *str, char *buff, unsigned int size)
{
	char			*new_str;
	size_t			len_str;
	size_t			i;

	len_str = 0;
	while (str && str[len_str])
		len_str++;
	new_str = malloc(len_str + size + 1);
	i = 0;
	while (new_str && str && i < len_str)
	{
		new_str[i] = str[i];
		i++;
	}
	i = 0;
	while (new_str && buff && i < size)
	{
		new_str[len_str + i] = buff[i];
		i++;
	}
	if (str)
		free(str);
	if (new_str)
		new_str[len_str + i] = 0;
	return (new_str);
}
