/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 02:05:05 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/19 22:17:04 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_CMD_LINE_H
# define READ_CMD_LINE_H

# include "tree.h"

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
}				t_token;

int	read_cmd_line(t_tree **cmd_line);

#endif
