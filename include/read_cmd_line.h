/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 02:05:05 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/27 18:14:17 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_CMD_LINE_H
# define READ_CMD_LINE_H

# include "tree.h"

# define LEXEME_NBR 12

typedef enum	e_lexeme
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

typedef struct	s_token
{
	t_lexeme	lexeme;
	int			i;
	int			size;
}	t_token;

typedef enum	e_redir_tag
{
	to_stdin = redir_stdin;
	heredoc = redir_heredoc;
	to_stdout = redir_stdout;
	append_to_stdout = redir_append_stdout;
	to_stderr = redir_stderr;
}	t_redir_tag;

typedef struct	s_redir
{
	t_redir_tag	tag;
	union
	{
		char	*pathfile;
		struct
		{
			int		is_quoted;
			char	*heredoc;
		}
	}
}	t_redir;

typedef struct	s_expression
{
	t_lexeme	lexeme;
	void		*content;
}	t_expression;

typedef enum	e_node_tag
{
	subprocess;
	list_or;
	list_and;
	pipeline;
	args;
}	t_node_tag;

typedef struct	s_node
{
	t_node_tag	tag;
	union
	{
		struct
		{
			int		*pipe_in;
			int		*pipe_out;
			t_redir	*redirs;
		};
		char	**args;
	}
}	t_node;

int	read_cmd_line(t_tree **cmd_line);

#endif
