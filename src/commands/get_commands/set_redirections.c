/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 00:03:00 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/10 17:45:24 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "list.h"
#include "minishell.h"

static int	set_stdin(t_command *cmd, const char *input, int input_size, int i)
{
	t_std	*std;
	t_list	*l_std;

	std = malloc(sizeof(t_std));
	if (!std)
		return (-1);
	std->pathfile = get_argument(input, input_size, i);
	if (!std->pathfile)
	{
		free(std);
		return (-1);
	}
	std->fd = 0;
	std->fd_redir = 0;
	std->append = 0;
	std->end = NULL;
	std->heredoc = 0;
	l_std = list_new(std);
	if (!l_std)
	{
		free_std(std);
		return (-1);
	}
	list_add_back(&cmd->std, l_std);
	return (0);
}

static int	set_stdout(t_command *cmd, const char *input, int input_size, int i)
{
	t_std	*std;
	t_list	*l_std;

	std = malloc(sizeof(t_std));
	if (!std)
		return (-1);
	std->pathfile = get_argument(input, input_size, i);
	if (!std->pathfile)
	{
		free(std);
		return (-1);
	}
	std->fd = 0;
	std->fd_redir = 1;
	std->append = 0;
	std->end = NULL;
	std->heredoc = 0;
	l_std = list_new(std);
	if (!l_std)
	{
		free_std(std);
		return (-1);
	}
	list_add_front(&cmd->std, l_std);
	return (0);
}

static int	set_stderr(t_command *cmd, const char *input, int input_size, int i)
{
	t_std	*std;
	t_list	*l_std;

	std = malloc(sizeof(t_std));
	if (!std)
		return (-1);
	std->pathfile = get_argument(input, input_size, i);
	if (!std->pathfile)
	{
		free(std);
		return (-1);
	}
	std->fd = 0;
	std->fd_redir = 2;
	std->append = 0;
	std->end = NULL;
	std->heredoc = 0;
	l_std = list_new(std);
	if (!l_std)
	{
		free_std(std);
		return (-1);
	}
	list_add_front(&cmd->std, l_std);
	return (0);
}

static int	set_append_stdout(t_command *cmd, const char *input,
	int input_size, int i)
{
	t_std	*std;
	t_list	*l_std;

	std = malloc(sizeof(t_std));
	if (!std)
		return (-1);
	std->pathfile = get_argument(input, input_size, i);
	if (!std->pathfile)
	{
		free(std);
		return (-1);
	}
	std->fd = 0;
	std->fd_redir = 1;
	std->append = 1;
	std->end = NULL;
	std->heredoc = 0;
	l_std = list_new(std);
	if (!l_std)
	{
		free_std(std);
		return (-1);
	}
	list_add_front(&cmd->std, l_std);
	return (0);
}

static int	set_heredoc(t_command *cmd, const char *input, int input_size,
	int i)
{
	t_std	*heredoc;
	t_list	*l_heredoc;

	heredoc = malloc(sizeof(t_std));
	if (!heredoc)
		return (-1);
	heredoc->end = get_argument(input, input_size, i);
	if (!heredoc->end)
	{
		free(heredoc);
		return (-1);
	}
	heredoc->pathfile = NULL;
	heredoc->fd = 0;
	heredoc->fd_redir = 0;
	heredoc->heredoc = 1;
	l_heredoc = list_new(heredoc);
	if (!l_heredoc)
	{
		free_std(heredoc);
		return (-1);
	}
	list_add_front(&cmd->std, l_heredoc);
	return (0);
}

int	set_redirections(t_command *cmd, const char *input, int input_size)
{
	const char			*redir_arg[] = {REDIR_STDIN, REDIR_HEREDOC,
		REDIR_STDOUT, REDIR_APPEND_STDOUT, REDIR_STDERR};
	const t_set_redir	set_redir[] = {&set_stdin, &set_heredoc,
		&set_stdout, &set_append_stdout, &set_stderr};
	int					i;
	int					i_r;

	i_r = 0;
	while (i_r < 5)
	{
		i = 0;
		skip_to(redir_arg[i_r], input, input_size, &i);
		while (i < input_size)
		{
			skip_to_next_argument(input, input_size, &i);
			if ((set_redir[i_r])(cmd, input, input_size, i) == -1)
				return (-1);
			skip_to(redir_arg[i_r], input, input_size, &i);
		}
		i_r++;
	}
	return (0);
}
