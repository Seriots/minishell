/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tidyer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:35:00 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/26 15:13:28 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "read_cmd_line.h"

int	get_size_tokens_tidy(t_token *tokens)
{
	int			count;
	int			i;

	count = 0;
	i = 0;
	while (tokens[i].lexeme != newline)
	{
		if (tokens[i].lexeme == argument)
		{
			count += 2;
			while (tokens[i].lexeme >= redir_heredoc)
				i++;
		}
		else
			i++;
	}
	count += i;
	return (count);
}

int	tidyer(t_token **tokens)
{
	t_token	*tokens_tidy;

	tokens_tidy = malloc(sizeof(t_token) * get_size_tokens_tidy(tokens));
	if (!tokens_tidy)
		return (-1);
	set_tokens_tidy(tokens_tidy, tokens);
	free(*tokens);
	*tokens = tokens_tidy;
	return (0);
}
