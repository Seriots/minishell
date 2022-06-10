/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_argument.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 23:59:10 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/09 17:02:32 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static void	skip_quotes(const char *input, int input_size, int *i)
{
	if (*i >= input_size)
		return ;
	if (input[*i] == '\"')
	{
		while (*i < input_size && input[*i] != '\"')
			*i += 1;
	}
	else if (input[*i] == '\'')
	{
		while (*i < input_size && input[*i] != '\'')
			*i += 1;
	}
	if (*i == input_size)
		ft_putstsr_fd("Warning: quote missing\n", 2);
}

static void	skip_parenthesis(const char *input, int input_size, int *i)
{
	int	nbr_parenthesis_to_close;

	if (*i >= input_size)
		return ;
	nbr_parenthesis_to_close = input[*i] == '(';
	while (*i < input_size && nbr_parenthesis_to_close)
	{
		*i += 1;
		nbr_parenthesis_to_close += input[*i] == '(';
		nbr_parenthesis_to_close -= input[*i] == ')';
	}
	if (*i == input_size)
		ft_putstsr_fd("Warning: parenthesis missing\n", 2);
}

void	skip_argument(const char *input, int input_size, int *i)
{
	if (is_argument_sep(input, input_size, *i))
	{
		skip_sep(input, input_size, i);
		return ;
	}
	while (*i < input_size && ft_strchr(END_SEP, input[*i]) == NULL)
	{
		skip_quotes(input, input_size, i);
		skip_parenthesis(input, input_size, i);
		if (*i < input_size)
			*i += 1;
	}
}
