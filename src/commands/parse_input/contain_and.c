/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contain_and.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:47:10 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/06 19:47:35 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	contain_and(const char *input, int input_size)
{
	int	size_and;
	int	i;

	size_and = ft_strlen(AND);
	i = 0;
	while (i < input_size - size_and)
	{
		if (ft_strncmp(input + i, AND, size_and) == 0)
			return (1);
		i++;
	}
	return (0);
}
