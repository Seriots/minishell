/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 00:03:00 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/07 01:49:54 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int	set_redir_stdin(t_command *cmd, const char *input, int input_size)
{
	if (cmd->heredoc_stdin)
		return (-1);
	cmd->redir_stdin = 1;
	cmd->pathfile_stdin = get_argument_after(REDIR_STDIN, input, input_size);
	if (!cmd->pathfile_stdin)
		return (-1);
	return (0);
}

static int	set_heredoc_stdin(t_command *cmd, const char *input, int input_size)
{
	if (cmd->redir_stdin)
		return (-1);
	cmd->heredoc_stdin = 1;
	cmd->end_heredoc = get_argument_after(REDIR_HEREDOC_STDIN, input,
		input_size);
	if (!cmd->end_heredoc)
		return (-1);
	return (0);
}

static int	set_redir_stdout(t_command *cmd, const char *input, int input_size)
{
	if (cmd->redir_append_stdout)
		return (-1);
	cmd->redir_stdout = 1;
	cmd->pathfile_stdout = get_argument_after(REDIR_STDOUT, input, input_size);
	if (!cmd->pathfile_stdout)
		return (-1);
	return (0);
}

static int	set_redir_append_stdout(t_command *cmd, const char *input,
	int input_size)
{
	if (cmd->redir_stdout)
		return (-1);
	cmd->redir_append_stdout = 1;
	cmd->pathfile_stdout = get_argument_after(REDIR_APPEND_STDOUT, input,
			input_size);
	if (!cmd->pathfile_stdout)
		return (-1);
	return (0);
}

int	set_redirections(t_command *cmd, const char *input, int input_size)
{
	const char			*redir_arg[] = {REDIR_STDIN, REDIR_HEREDOC_STDIN,
		REDIR_STDOUT, REDIR_APPEND_STDOUT};
	const t_set_redir	set_redir[] = {&set_redir_stdin, &set_heredoc_stdin,
		&set_redir_stdout, &set_redir_append_stdout};
	int					i;

	i = 0;
	while (i < REDIR_NBR)
	{
		if (is_argument_in_input(redir_arg[i], input, input_size))
			if ((set_redir[i])(cmd, input, input_size) == -1)
				return (-1);
		i++;
	}
	return (0);
}
