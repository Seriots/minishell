/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:27:50 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/20 15:29:13 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../include/libft.h"
#include "../../include/ft_printf.h"
#include "../../include/list.h"

int	get_next_str(char *str, unsigned int pos)
{
	unsigned int	i;

	while (str[pos] && str[pos] != '*')
		pos ++;
	while (str[pos] && str[pos] == '*')
		pos ++;
	if (!str[pos])
		return (-1);
	i = 1;
	while (str[pos + i])
	{
		if (str[pos + i] == '*')
			return (pos);
		i++;
	}
	return (-1);
}

char	*get_substr(char *str, unsigned int pos)
{
	unsigned int	length;
	char			*result;
	unsigned int	i;

	length = 0;
	while (str[pos + length] && str[pos + length] != '*')
		length ++;
	if (!str[pos + length])
		return (0);
	result = ft_calloc(sizeof(char), length + 1);
	if (!result)
		return (0);
	i = 0;
	while (i < length)
	{
		result[i] = str[pos + i];
		i ++;
	}
	return (result);
}

unsigned int	is_substr(char *input, unsigned int pos, char *substr)
{
	unsigned int	i;

	if (!substr)
		return (0);
	if (!substr[0])
		return (1);
	i = 0;
	while (substr[i])
	{
		if (input[pos + i] != substr[i])
			return (0);
		i ++;
	}
	return (i);
}

int	comp(char *s1, char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i ++;
	return (s1[i] != s2[i]);
}

size_t	get_size_list_contents(t_list *wildcards)
{
	size_t	size;

	size = 0;
	while (wildcards)
	{
		size += ft_strlen(wildcards->content);
		wildcards = wildcards->next;
	}
	return (size);
}
