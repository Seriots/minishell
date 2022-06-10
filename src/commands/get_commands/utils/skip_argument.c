/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_argument.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 23:59:10 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/10 21:05:37 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int	skip_quotes(const char *input, int input_size, int *i)
{
	if (*i >= input_size || (input[*i] != '\"' && input[*i] != '\''))
		return (0);
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
	if (*i >= input_size)
		ft_putstr_fd("Warning: quote missing\n", 2);
	*i += 1;
	return (1);
}

static int	skip_parenthesis(const char *input, int input_size, int *i)
{
	int	nbr_parenthesis_to_close;

	if (*i >= input_size || input[*i] != '(')
		return (0);
	nbr_parenthesis_to_close = 1;
	*i += 1;
	while (*i < input_size && nbr_parenthesis_to_close)
	{
		nbr_parenthesis_to_close += input[*i] == '(';
		nbr_parenthesis_to_close -= input[*i] == ')';
		if (skip_quotes(input, input_size, i))
			continue ;
		*i += 1;
	}
	if (nbr_parenthesis_to_close)
		ft_putstr_fd("Warning: parenthesis missing\n", 2);
	return (1);
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
		if (skip_parenthesis(input, input_size, i))
			continue ;
		if (skip_quotes(input, input_size, i))
			continue ;
		*i += 1;
	}
}
