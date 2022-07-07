/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 19:11:31 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/07 13:00:08 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

size_t	get_size_minus_q(char *input)
{
	size_t	size;
	size_t	i;
	char	quote;

	size = ft_strlen(input);
	i = 0;
	quote = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (quote == 0)
			{
				size--;
				quote = input[i];
			}
			else if (input[i] == quote)
			{
				size --;
				quote = 0;
			}	
		}
		i ++;
	}
	return (size);
}

void	get_str_minus_q(char **new, char *input)
{
	size_t	i;
	size_t	size;
	char	quote;

	i = 0;
	size = 0;
	quote = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (quote == 0)
				quote = input[i];
			else if (input[i] == quote)
				quote = 0;
		}
		if (!(input[i] == quote
				|| ((input[i] == '\'' || input[i] == '\"') && quote == 0)))
			(*new)[size++] = input[i];
		i ++;
	}
}

char	*remove_quotes(char *input)
{
	size_t	size;
	char	*new;

	size = get_size_minus_q(input);
	new = ft_calloc(sizeof(char), size + 1);
	if (!new)
	{
		free (input);
		return (0);
	}
	get_str_minus_q(&new, input);
	free(input);
	return (new);
}

char	**removes_quotes(char **input)
{
	int	i;

	if (!input)
		return (0);
	i = 0;
	while (input[i])
	{
		input[i] = remove_quotes(input[i]);
		if (!input[i])
		{
			while (input[++i])
				free (input[i]);
			ft_free_tab(input);
			return (0);
		}
		i++;
	}
	return (input);
}
