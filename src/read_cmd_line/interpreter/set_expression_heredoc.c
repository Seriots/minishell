/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_expression_heredoc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 18:53:21 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/06 04:16:57 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "libft.h"
#include "minishell.h"
#include "read_cmd_line.h"

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
			i++;
			while (end[i++] != '\'')
				end[j++] = end[i];
		}
		else if (end[i] == '\'')
		{
			i++;
			while (end[i++] != '\'')
				end[j++] = end[i];
		}
		else
			end[j++] = end[i++];
	}
}

static char	*get_heredoc(const char *end)
{
	char	*line;
	char	*heredoc;

	heredoc = NULL;
	line = readline(PROMPT_HEREDOC);
	while (ft_strcmp(line, end) != 0)
	{
		ft_strjoin_onplace(&heredoc, line);
		ft_strjoin_onplace(&heredoc, "\n");
		if (!heredoc)
			return (NULL);
		line = readline(PROMPT_HEREDOC);
	}
	return (heredoc);
}

int	set_expression_heredoc(t_expression *expression, t_token *token,
	const char *input)
{
	char	*end;
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (-1);
	redir->tag = (t_redir_tag) token->lexeme;
	end = ft_strndup(input + token->i, token->size);
	if (!end)
		return (-1);
	redir->is_quoted = is_end_quoted(end);
	remove_quotes_onplace(end);
	redir->heredoc = get_heredoc(end);
	free(end);
	if (!redir->heredoc)
		return (free(redir), -1);
	expression->content = redir;
	return (0);
}
