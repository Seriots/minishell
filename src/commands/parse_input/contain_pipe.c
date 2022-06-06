/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contain_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:47:50 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/06 19:48:06 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	contain_pipe(const char *input, int input_size)
{
	int	size_pipe;
	int	i;

	size_pipe = ft_strlen(PIPE);
	i = 0;
	while (i < input_size - size_pipe)
	{
		if (ft_strncmp(input + i, PIPE, size_pipe) == 0)
			return (1);
		i++;
	}
	return (0);
}
