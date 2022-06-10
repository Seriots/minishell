/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 00:03:00 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/10 09:45:02 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "list.h"
#include "minishell.h"

static int	set_redir_stdin(t_command *cmd, const char *input, int input_size,
	int i)
{
	char	*pathfile_stdin;
	t_list	*l_pathfile_stdin;

	if (cmd->heredoc_stdin)
		return (-1);
	cmd->redir_stdin = 1;
	pathfile_stdin = get_argument(input, input_size, i);
	if (!pathfile_stdin)
		return (-1);
	l_pathfile_stdin = list_new(pathfile_stdin);
	if (!l_pathfile_stdin)
	{
		free(pathfile_stdin);
		return (-1);
	}
	list_add_front(&cmd->pathfile_stdin, l_pathfile_stdin);
	return (0);
}

static int	set_heredoc_stdin(t_command *cmd, const char *input, int input_size,
	int i)
{
	char	*end_heredoc;
	t_list	*l_end_heredoc;

	if (cmd->redir_stdin)
		return (-1);
	cmd->heredoc_stdin = 1;
	end_heredoc = get_argument(input, input_size, i);
	if (!end_heredoc)
		return (-1);
	l_end_heredoc = list_new(end_heredoc);
	if (!l_end_heredoc)
	{
		free(end_heredoc);
		return (-1);
	}
	list_add_front(&cmd->end_heredoc, l_end_heredoc);
	return (0);
}

static int	set_redir_stdout(t_command *cmd, const char *input, int input_size,
	int i)
{
	char	*pathfile_stdout;
	t_list	*l_pathfile_stdout;

	if (cmd->redir_append_stdout)
		return (-1);
	cmd->redir_stdout = 1;
	pathfile_stdout = get_argument(input, input_size, i);
	if (!pathfile_stdout)
		return (-1);
	l_pathfile_stdout = list_new(pathfile_stdout);
	if (!l_pathfile_stdout)
	{
		free(pathfile_stdout);
		return (-1);
	}
	list_add_front(&cmd->pathfile_stdout, l_pathfile_stdout);
	return (0);
}

static int	set_redir_append_stdout(t_command *cmd, const char *input,
	int input_size, int i)
{
	char	*pathfile_stdout;
	t_list	*l_pathfile_stdout;

	if (cmd->redir_stdout)
		return (-1);
	cmd->redir_append_stdout = 1;
	pathfile_stdout = get_argument(input, input_size, i);
	if (!pathfile_stdout)
		return (-1);
	l_pathfile_stdout = list_new(pathfile_stdout);
	if (!l_pathfile_stdout)
	{
		free(pathfile_stdout);
		return (-1);
	}
	list_add_front(&cmd->pathfile_stdout, l_pathfile_stdout);
	return (0);
}

static int	set_redir_stderr(t_command *cmd, const char *input, int input_size,
	int i)
{
	char	*pathfile_stderr;
	t_list	*l_pathfile_stderr;

	if (cmd->redir_append_stderr)
		return (-1);
	cmd->redir_stderr = 1;
	pathfile_stderr = get_argument(input, input_size, i);
	if (!pathfile_stderr)
		return (-1);
	l_pathfile_stderr = list_new(pathfile_stderr);
	if (!l_pathfile_stderr)
	{
		free(pathfile_stderr);
		return (-1);
	}
	list_add_front(&cmd->pathfile_stderr, l_pathfile_stderr);
	return (0);
}

int	set_redirections(t_command *cmd, const char *input, int input_size)
{
	const char			*redir_arg[] = {REDIR_STDIN, REDIR_HEREDOC_STDIN,
		REDIR_STDOUT, REDIR_APPEND_STDOUT, REDIR_STDERR};
	const t_set_redir	set_redir[] = {&set_redir_stdin, &set_heredoc_stdin,
		&set_redir_stdout, &set_redir_append_stdout, &set_redir_stderr};
	int					i;
	int					i_r;

	i_r = 0;
	while (i_r < REDIR_NBR)
	{
		i = 0;
		skip_to(redir_arg[i_r], input, input_size, &i);
		while (i < input_size)
		{
			skip_to_next_argument(input, input_size, &i);
			if ((set_redir[i_r])(cmd, input, input_size, i) == -1)
				return (-1);
			skip_to(redir_arg[i_r], input, input_size);
		}
		i_r++;
	}
	return (0);
}
