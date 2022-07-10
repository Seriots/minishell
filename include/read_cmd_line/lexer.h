/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 01:57:02 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/10 21:43:17 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "read_cmd_line.h"

# define WHITESPACES "\t\v\f\r\n "
# define END_ARG "\t\v\f\r\n ()|&<>"

# define NEWLINE_STR "\n"
# define PARENTHESIS_LEFT_STR "("
# define PARENTHESIS_RIGHT_STR ")"
# define LOGICAL_OR_STR "||"
# define LOGICAL_AND_STR "&&"
# define PIPE_STR "|"
# define REDIR_HEREDOC_STR "<<"
# define REDIR_STDIN_STR "<"
# define REDIR_APPEND_STDOUT_STR ">>"
# define REDIR_STDOUT_STR ">"
# define REDIR_STDERR_STR "2>"
# define ARGUMENT_STR ""

typedef struct s_lexer_state
{
	t_lexeme	lexeme;
	int			i;
	int			size;
}	t_lexer_state;

int			lexer(t_token **tokens, const char *input);
t_lexeme	lexer_get_lexeme(const char *input);
int			lexer_init_state(t_lexer_state *lexer, const char *input);
int			lexer_set_size(t_lexer_state *lexer, const char *input);
int			lexer_update_state(t_lexer_state *lexer, const char *input);

#endif
