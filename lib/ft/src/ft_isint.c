/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:12:43 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/05/12 15:41:44 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

int	ft_isint(const char *str)
{
	size_t	size_int;
	size_t	i;

	size_int = 0;
	i = 0;
	while (size_int < 10 && ft_isdigit(str[i]))
	{
		size_int++;
		i++;
	}
	if (size_int == 10 && ft_strncmp(str, "2147483647", 10) > 0)
		return (0);
	return (1);
}
