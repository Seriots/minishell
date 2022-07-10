/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_expression_heredoc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 18:53:21 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/10 23:31:47 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cmd_line.h"
#include "libft.h"
#include "read_cmd_line.h"
#include "shell.h"

extern t_shell_status	g_shell_status;

static int	is_end_quoted(const char *end)
{
	int	count_quote;
	int	count_double_quote;

	count_quote = 0;
	count_double_quote = 0;
	while (*end)
	{
		if (*end == '\'')
			count_quote++;
		if (*end == '\"')
			count_double_quote++;
		end++;
	}
	return (count_quote >= 2 || count_double_quote >= 2);
}

static void	remove_quotes_onplace(char *end)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (end[i])
	{
		if (end[i] == '\'')
		{
			while (end[++i] != '\'')
				end[j++] = end[i];
			i++;
		}
		else if (end[i] == '\'')
		{
			while (end[++i] != '\'')
				end[j++] = end[i];
			i++;
		}
		else
			end[j++] = end[i++];
	}
	end[j] = 0;
}

static void	manage_warning_use_eof_in_heredoc(const char *end)
{
	ft_putstr_fd(WARNING_USE_EOF_IN_HEREDOC_1, 2);
	ft_putstr_fd(end, 2);
	ft_putstr_fd(WARNING_USE_EOF_IN_HEREDOC_2, 2);
}

static char	*get_heredoc(char *end, t_shell *shell)
{
	char	*heredoc;

	heredoc = malloc(1);
	if (!heredoc)
		return (NULL);
	*heredoc = 0;
	while (1)
	{
		set_input(PROMPT_HEREDOC, shell);
		if (g_shell_status == reading_cmd_line)
			return (free(heredoc), NULL);
		if (!shell->input)
			manage_warning_use_eof_in_heredoc(end);
		if (!shell->input || ft_strcmp(shell->input, end) == 0)
			break ;
		if (ft_strjoin_onplace(&heredoc, shell->input) == -1)
			return (free(shell->input), free(heredoc), NULL);
		if (ft_strjoin_onplace(&heredoc, "\n") == -1)
			return (free(shell->input), free(heredoc), NULL);
		free(shell->input);
	}
	free(shell->input);
	return (heredoc);
}

int	set_expression_heredoc(t_expression *expression, t_token *token,
	t_shell *shell)
{
	char	*end;
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (-1);
	redir->tag = (t_redir_tag) token->lexeme;
	end = ft_strndup(shell->cmd_line_input + token->i, token->size);
	if (!end)
		return (-1);
	redir->is_quoted = is_end_quoted(end);
	remove_quotes_onplace(end);
	redir->heredoc = get_heredoc(end, shell);
	free(end);
	if (!redir->heredoc)
		return (free(redir), -1);
	expression->content = redir;
	return (0);
}
