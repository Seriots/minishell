/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:47:03 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/12 15:52:39 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (*(s + i))
		i ++;
	return (i);
}

char	*ft_strjoin2_gnl(char *s1, char *s2, char *result, size_t s1_size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1_size && s1[i])
	{
		result[i] = s1[i];
		i ++;
	}
	while (s2[j])
	{
		result[i + j] = s2[j];
		j++;
	}
	return (result);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*result;
	size_t	s1_size;
	size_t	s2_size;

	if (s1 == 0)
		s1_size = 0;
	else
		s1_size = ft_strlen_gnl(s1);
	s2_size = ft_strlen_gnl(s2);
	if (s1_size + s2_size == 0)
	{
		free(s1);
		return (0);
	}
	result = malloc(sizeof(char) * (s1_size + s2_size + 1));
	if (!result)
		return (0);
	result[s1_size + s2_size] = 0;
	result = ft_strjoin2_gnl(s1, s2, result, s1_size);
	free(s1);
	return (result);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	if (!s)
		return (0);
	while (*(s + i))
	{
		if ((*(s + i) == (char)c))
		{
			ptr = (char *)s + i;
			return (ptr);
		}
		i ++;
	}
	if (*(s + i) == (char)c)
	{
		ptr = (char *)s + i;
		return (ptr);
	}
	return (0);
}

void	ft_copy2_gnl(char *dest, char *src)
{
	int		size;
	int		i;

	i = 0;
	if (!dest)
		return ;
	if (!src)
	{
		dest[0] = 0;
		return ;
	}
	size = ft_strlen_gnl(src);
	dest[size] = 0;
	while (i < size)
	{
		dest[i] = src[i];
		i ++;
	}
}
