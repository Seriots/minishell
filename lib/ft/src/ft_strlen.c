/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:25:29 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/11 01:30:07 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *str)
{
	int	size;

	size = 0;
	if (!str)
		return (0);
	while (*str)
	{
		size++;
		str++;
	}
	return (size);
}
