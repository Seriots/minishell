/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_expression_heredoc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 18:53:21 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/08 12:16:43 by lgiband          ###   ########.fr       */
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

char	*get_line_heredoc(void)
{
	char	*line;
	char	tmp[1 + BUFFER_HEREDOC];
	int		readed;

	ft_printf(PROMPT_HEREDOC);
	readed = BUFFER_HEREDOC;
	line = 0;
	while (readed == BUFFER_HEREDOC)
	{
		readed = read(0, tmp, BUFFER_HEREDOC);
		tmp[readed] = 0;
		ft_strjoin_onplace(&line, tmp);
		if (!line)
			return (0);
		if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
			return (line);
	}
	return (line);
}

char	*manage_error_heredoc(char *heredoc, char *line, char *end)
{
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
	free(line);
	return (heredoc);
}

int	read_heredoc(char **heredoc, char **line, char **line_cpy)
{
	ft_strjoin_onplace(heredoc, *line);
	if (!*heredoc)
		return (free(*line), free(*line_cpy), 1);
	if (!ft_strlen(*line) || (*line)[ft_strlen(*line) - 1] != '\n')
	{
		printf("\n");
		return (2);
	}
	free(*line_cpy);
	free(*line);
	*line = get_line_heredoc();
	*line_cpy = ft_strtrim(*line, "\n");
	if (!*line_cpy)
		return (free(*line), free(*heredoc), 1);
	return (0);
}	

static char	*get_heredoc(char *end)
{
	char				*heredoc;
	char				*line;
	char				*line_cpy;
	int					ret;
	struct sigaction	sigact;

	heredoc = NULL;
	sigact = init_sigact_heredoc();
	sigaction(SIGINT, &sigact, NULL);
	line = get_line_heredoc();
	line_cpy = ft_strtrim(line, "\n");
	if (!line_cpy)
		return (free(line), free(heredoc), NULL);
	while (line && ft_strcmp(line_cpy, end) != 0)
	{
		ret = read_heredoc(&heredoc, &line, &line_cpy);
		if (ret == 2)
			break ;
		if (ret == 1)
			return (0);
	}
	free(line_cpy);
	return (manage_error_heredoc(heredoc, line, end));
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
