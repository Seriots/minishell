/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_update_state.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 00:30:57 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/04 22:50:51 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

static void	lexer_skip_whitespaces(t_lexer_state *lexer, const char *input)
{
	while (input[lexer->i] && ft_strchr(WHITESPACES, input[lexer->i]) != NULL
		&& input[lexer->i] != '\n')
		lexer->i += 1;
}

int	lexer_update_state(t_lexer_state *lexer, const char *input)
{
	lexer->i += lexer->size;
	lexer_skip_whitespaces(lexer, input);
	lexer->lexeme = lexer_get_lexeme(input + lexer->i);
	if (lexer_set_size(lexer, input) == -1)
		return (-1);
	return (0);
}
