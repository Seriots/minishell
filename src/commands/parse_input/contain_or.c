/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contain_or.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:41:37 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/06 19:46:57 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	contain_or(const char *input, int input_size)
{
	int	size_or;
	int	i;

	size_or = ft_strlen(OR);
	i = 0;
	while (i < input_size - size_or)
	{
		if (ft_strncmp(input + i, OR, size_or) == 0)
			return (1);
		i++;
	}
	return (0);
}
