/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_argument.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 23:59:10 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/07 00:31:13 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	skip_argument(const char *input, int input_size, int *i)
{
	while (*i < input_size && ft_strchr(WHITESPACES, input[*i]) == NULL)
	{
		if (*i < input_size && input[*i] == '\"')
		{
			*i += 1;
			while (*i < input_size && input[*i] != '\"')
				*i += 1;
		}
		else if (*i < input_size && input[*i] == '\'')
		{
			*i += 1;
			while (*i < input_size && input[*i] != '\'')
				*i += 1;
		}
		else
			*i += 1;
	}
}
