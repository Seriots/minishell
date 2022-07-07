/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 02:05:05 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/07 03:39:48 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_CMD_LINE_H
# define READ_CMD_LINE_H

# include "tree.h"
# define PROMPT_SHELL "\033[48:5:235m\033[0J\033[38:5:33mGsh$> \033[38:5:15m"
# define PROMPT_HEREDOC "> "
# define WARNING_EOF_EXPECTED "warning: here-document at line 1 delimited by \
end-of-file (wanted `"

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
int	interpreter_input(t_expression **expressions, t_token *tokens,
		const char *input);
int	set_expression_heredoc(t_expression *expression, t_token *token,
		const char *input);
typedef int	(*t_set_expression_content)(t_expression *, t_token *,
	const char *);

/*
//	PARSER
*/
int	count_lexeme(t_expression *expressions, t_lexeme lexeme);
int	get_indice_next_lexeme(t_expression *expressions, int i, t_lexeme lexeme);
int	parser(t_tree **cmd_line, t_expression *expressions);
int	parser_and(t_tree **cmd_line, t_expression *expressions);
int	parser_args(t_tree **cmd_line, t_expression *expressions);
int	parser_or(t_tree **cmd_line, t_expression *expressions);
int	parser_parenthesis(t_tree **cmd_line, t_expression *expressions);
int	parser_pipe(t_tree **cmd_line, t_expression *expressions);

/*
//	READ_CMD_LINE
*/
int	read_cmd_line(t_tree **cmd_line);

#endif
