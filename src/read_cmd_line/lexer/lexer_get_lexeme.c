/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_lexeme.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 01:42:49 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/19 23:32:10 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "read_cmd_line.h"

t_lexeme	lexer_get_lexeme(const char *input)
{
	const char	*lexeme_str[] = {NEWLINE_STR, PARENTHESIS_LEFT_STR,
		PARENTHESIS_RIGHT_STR, LOGICAL_OR_STR, LOGICAL_AND_STR, PIPE_STR,
		REDIR_HEREDOC_STR, REDIR_STDIN_STR, REDIR_APPEND_STDOUT_STR,
		REDIR_STDOUT_STR, REDIR_STDERR_STR};
	t_lexeme	lex;

	lex = 0;
	while (lex != argument
		&& ft_strncmp(input, lexeme_str[lex], ft_strlen(lexeme_str[lex])) != 0)
		lex++;
	return (lex);
}
