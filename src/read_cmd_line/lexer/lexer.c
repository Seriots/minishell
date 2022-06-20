/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 23:31:52 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/20 00:12:25 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "read_cmd_line.h"

static int	lexer_error_format(const char *input)
{
	t_lexer_state	lexer;

	if (lexer_init_state(&lexer, input) == -1)
		return (1);
	while (lexer.lexeme != newline)
		if (lexer_update_state(&lexer, input) == -1)
			return (1);
	return (0);
}

static int	lexer_count_tokens(const char *input)
{
	int				count;
	t_lexer_state	lexer;

	count = 0;
	lexer_init_state(&lexer, input);
	while (lexer.lexeme != newline)
	{
		count++;
		lexer_update_state(&lexer, input);
	}
	count++;
	return (count);
}

static void	lexer_set_token(t_token *token, t_lexer_state *lexer)
{
	token->lexeme = lexer->lexeme;
	token->i = lexer->i;
	token->size = lexer->size;
}

static int	lexer_set_tokens(t_token *tokens, const char *input)
{
	int				i_token;
	t_lexer_state	lexer;

	i_token = 0;
	lexer_init_state(&lexer, input);
	while (lexer.lexeme != newline)
	{
		lexer_set_token(tokens + i_token, &lexer);
		i_token++;
		lexer_update_state(&lexer, input);
	}
	lexer_set_token(tokens + i_token, &lexer);
	return (0);
}

int	lexer(const char *input, t_token **tokens)
{
	int	nbr_tokens;

	if (lexer_error_format(input))
		return (-1);
	nbr_tokens = lexer_count_tokens(input);
	*tokens = malloc(sizeof(t_token) * nbr_tokens);
	if (!*tokens)
		return (-1);
	lexer_set_tokens(*tokens, input);
	return (0);
}
