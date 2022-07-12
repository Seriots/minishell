/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:16:28 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/12 20:55:49 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_LINE_H
# define CMD_LINE_H

# include "read_cmd_line.h"

typedef enum e_redir_tag
{
	to_stdin = redir_stdin,
	heredoc = redir_heredoc,
	to_stdout = redir_stdout,
	append_to_stdout = redir_append_stdout,
	to_stderr = redir_stderr
}	t_redir_tag;

typedef struct s_redir
{
	t_redir_tag	tag;
	union
	{
		char	*pathfile;
		struct
		{
			int		is_quoted;
			char	*heredoc;
		};
	};
}	t_redir;

typedef enum e_node_tag
{
	list_or,
	list_and,
	pipeline,
	args
}	t_node_tag;

typedef struct s_node
{
	t_node_tag	tag;
	char		**args;
	t_redir		**redirs;
}	t_node;

void	free_cmd_line(void *node_addr);
void	free_cmd_line_struct(void *node_addr);
void	free_redir(t_redir *redir);

#endif
