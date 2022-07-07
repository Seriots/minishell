/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_expression_heredoc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 18:53:21 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/07 22:45:51 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h>
#include "ft_printf.h"
#include "get_next_line.h"
#include "libft.h"
#include "minishell.h"
#include "read_cmd_line.h"

extern int	g_stop_run;

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

char	*get_line_heredoc(void)
{
	char	*line;

	ft_printf(PROMPT_HEREDOC);
	line = 0;
	line = get_next_line(0);
	return (line);
}

static char	*get_heredoc(char *end)
{
	char				*heredoc;
	char				*line;
	struct sigaction	sigact;

	heredoc = NULL;
	sigact = init_sigact_heredoc();
	sigaction(SIGINT, &sigact, NULL);
	line = get_line_heredoc();
	while (line && ft_strcmp(ft_strtrim(line, "\n"), end) != 0)
	{
		ft_strjoin_onplace(&heredoc, line);
		if (!heredoc)
			return (NULL);
		if (line[ft_strlen(line) - 1] != '\n')
		{
			printf("\n");
			break ;
		}
		free(line);
		line = get_line_heredoc();
			
	}
	if (g_stop_run == 4)
		printf("\n");
	if (!heredoc)
		heredoc = ft_calloc(sizeof(char), 1);
	if (!line && g_stop_run != 4)
	{
		ft_putstr_fd(WARNING_EOF_EXPECTED, 2);
		ft_putstr_fd(end, 2);
		ft_putstr_fd("')\n", 2);
	}
	return (free(line), heredoc);
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
