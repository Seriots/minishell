/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tokens_tidy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 15:13:38 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/26 15:20:02 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_cmd_line.h"

void	set_token(t_token **tokens_tidy, t_lexeme lexeme, int i, int size)
{
	(*tokens_tidy)->lexeme = lexeme;
	(*tokens_tidy)->i = i;
	(*tokens_tidy)->size = size;
	*tokens_tidy += 1;
}

void	set_tidy_args(t_token **tokens_tidy, t_token *tokens)
{
	while (tokens->lexeme >= redir_heredoc)
	{
		if (tokens->lexeme == argument)
			set_token(tokens_tidy, tokens->lexeme, tokens->i, tokens->size);
		tokens++;
	}
}

void	set_tidy_args(t_token **tokens_tidy, t_token *tokens)
{
	while (tokens->lexeme >= redir_heredoc)
	{
		if (tokens->lexeme != argument)
			set_token(tokens_tidy, tokens->lexeme, tokens->i, tokens->size);
		tokens++;
	}
}

void	skip_args(t_token **tokens)
{
	while (tokens->lexeme >= redir_heredoc)
		tokens++;
}

void	set_tokens_tidy(t_token *tokens_tidy, t_token *tokens)
{
	while (tokens->lexeme != newline)
	{
		if (tokens[i].lexeme == argument)
		{
			set_token(&tokens_tidy, parenthesis_left, -1, -1);
			set_tidy_args(&tokens_tidy, tokens);
			set_token(&tokens_tidy, parenthesis_right, -1, -1);
			set_tidy_redirs(&tokens_tidy, tokens);
			skip_args(&tokens);
		}
		else
		{
			set_token_tidy(tokens_tidy, tokens);
			tokens++;
			tokens_tidy++;
		}
	}
}
