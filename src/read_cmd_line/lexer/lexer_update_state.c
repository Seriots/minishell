/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_update_state.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 00:30:57 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/13 23:41:53 by rgarrigo         ###   ########.fr       */
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

static void	manage_size_error(t_lexer_state *lexer, const char *input)
{
	const char	*lexeme_str[] = {NEWLINE_STR, PARENTHESIS_LEFT_STR,
		PARENTHESIS_RIGHT_STR, LOGICAL_OR_STR, LOGICAL_AND_STR, PIPE_STR,
		REDIR_HEREDOC_STR, REDIR_STDIN_STR, REDIR_APPEND_STDOUT_STR,
		REDIR_STDOUT_STR, REDIR_STDERR_STR};
	t_lexeme	next_lexeme;

	lexer->i += ft_strlen(lexeme_str[lexer->lexeme]);
	lexer_skip_whitespaces(lexer, input);
	next_lexeme = lexer_get_lexeme(input + lexer->i);
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (next_lexeme == newline)
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd(lexeme_str[next_lexeme], 2);
	ft_putstr_fd("'\n", 2);
}

int	lexer_update_state(t_lexer_state *lexer, const char *input)
{
	lexer->i += lexer->size;
	lexer_skip_whitespaces(lexer, input);
	lexer->lexeme = lexer_get_lexeme(input + lexer->i);
	if (lexer_set_size(lexer, input) == -1)
		return (manage_size_error(lexer, input), -1);
	return (0);
}
