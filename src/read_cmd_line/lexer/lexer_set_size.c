/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_set_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 01:15:32 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/04 22:07:59 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "lexer.h"
#include "libft.h"
#include "read_cmd_line.h"

static int	lexer_get_argument_size(const char *input)
{
	int	j;

	j = 0;
	while (input[j] && ft_strchr(END_ARG, input[j]) == NULL)
	{
		if (input[j] == '\"')
		{
			j++;
			while (input[j] && input[j] != '\n' && input[j] != '\"')
				j++;
		}
		if (input[j] == '\'')
		{
			j++;
			while (input[j] && input[j] != '\n' && input[j] != '\'')
				j++;
		}
		if (input[j] && input[j] != '\n')
			j++;
	}
	return (j);
}

static int	lexer_is_lexeme_redir(t_lexeme lexeme)
{
	int	is_redir;

	is_redir = lexeme == redir_stdin;
	is_redir |= lexeme == redir_stdout;
	is_redir |= lexeme == redir_stderr;
	is_redir |= lexeme == redir_append_stdout;
	is_redir |= lexeme == redir_heredoc;
	return (is_redir);
}

static int	lexer_get_lexeme_size(t_lexeme lexeme)
{
	const char	*lexeme_str[] = {NEWLINE_STR, PARENTHESIS_LEFT_STR,
		PARENTHESIS_RIGHT_STR, LOGICAL_OR_STR, LOGICAL_AND_STR, PIPE_STR,
		REDIR_HEREDOC_STR, REDIR_STDIN_STR, REDIR_APPEND_STDOUT_STR,
		REDIR_STDOUT_STR, REDIR_STDERR_STR, ARGUMENT_STR};

	return (ft_strlen(lexeme_str[lexeme]));
}

static int	lexer_set_redir_size(t_lexer_state *lexer, const char *input)
{
	int	i;
	int	j;

	i = lexer->i;
	j = lexer_get_lexeme_size(lexer->lexeme);
	while (input[i + j] && ft_strchr(WHITESPACES, input[i + j]) != NULL)
		j++;
	if (!input[i + j] || lexer_get_lexeme(input + i + j) != argument)
		return (-1);
	j += lexer_get_argument_size(input + i + j);
	lexer->size = j;
	return (0);
}

int	lexer_set_size(t_lexer_state *lexer, const char *input)
{
	if (lexer_is_lexeme_redir(lexer->lexeme))
		return (lexer_set_redir_size(lexer, input));
	if (lexer->lexeme != argument)
		lexer->size = lexer_get_lexeme_size(lexer->lexeme);
	if (lexer->lexeme == argument)
		lexer->size = lexer_get_argument_size(input + lexer->i);
	return (0);
}
