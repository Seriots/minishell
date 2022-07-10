/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 02:05:05 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/10 22:51:32 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_CMD_LINE_H
# define READ_CMD_LINE_H

# include "shell.h"
# include "tree.h"

# define PROMPT_SHELL "\1\033[48:5:235m\033[0J\033[38:5:33m\2Gsh$> \
\1\033[38:5:15m\2"
# define PROMPT_HEREDOC "> "
# define WARNING_USE_EOF_IN_HEREDOC_1 "warning: here-document delimited by \
end-of-file (wanted `"
# define WARNING_USE_EOF_IN_HEREDOC_2 "')\n"

typedef enum e_lexeme
{
	newline,
	parenthesis_left,
	parenthesis_right,
	logical_or,
	logical_and,
	pipe_lexeme,
	redir_heredoc,
	redir_stdin,
	redir_append_stdout,
	redir_stdout,
	redir_stderr,
	argument
}	t_lexeme;

typedef struct s_token
{
	t_lexeme	lexeme;
	int			i;
	int			size;
}	t_token;

typedef struct s_expression
{
	t_lexeme	lexeme;
	void		*content;
}	t_expression;

/*
//	INTERPRETER
*/
typedef int	(*t_set_expression_content)(t_expression *, t_token *,
	t_shell *);

int		interpreter_input(t_expression **expressions, t_token *tokens,
			t_shell *shell);
int		set_expression_heredoc(t_expression *expression, t_token *token,
			t_shell *shell);

/*
//	PARSER
*/
int		count_lexeme(t_expression *expressions, t_lexeme lexeme);
int		get_indice_next_lexeme(t_expression *expressions, int i, t_lexeme lexeme);
int		parser_and(t_tree **cmd_line, t_expression *expressions);
int		parser_args(t_tree **cmd_line, t_expression *expressions);
int		parser_or(t_tree **cmd_line, t_expression *expressions);
int		parser_parenthesis(t_tree **cmd_line, t_expression *expressions);
int		parser_pipe(t_tree **cmd_line, t_expression *expressions);
int		parser(t_tree **cmd_line, t_expression *expressions);

/*
//	READ_CMD_LINE
*/
int		read_cmd_line(t_tree **cmd_line, t_shell *shell);
void	set_input(const char *prompt, t_shell *shell);

#endif
