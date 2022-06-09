/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_argument.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 23:59:10 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/09 03:00:04 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	skip_argument(const char *input, int input_size, int *i)
{
	if (is_argument_redirection(input, input_size, *i))
	{
		skip_redirection(input, input_size, i);
		return ;
	}
	while (*i < input_size && ft_strchr(END_SEP, input[*i]) == NULL)
	{
		if (input[*i] == '\"')
		{
			*i += 1;
			while (*i < input_size && input[*i] != '\"')
				*i += 1;
		}
		else if (input[*i] == '\'')
		{
			*i += 1;
			while (*i < input_size && input[*i] != '\'')
				*i += 1;
		}
		else
			*i += 1;
	}
}
