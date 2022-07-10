/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 23:09:56 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/10 23:24:56 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "cmd_line.h"
#include "read_cmd_line.h"
#include "shell.h"

static int	count_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].lexeme != newline)
		i++;
	i++;
	return (i);
}

static int	set_expression_argument(t_expression *expression, t_token *token,
	t_shell *shell)
{
	expression->content = ft_strndup(shell->cmd_line_input + token->i,
			token->size);
	if (!expression->content)
		return (-1);
	return (0);
}

static int	set_expression_redir(t_expression *expression, t_token *token,
	t_shell *shell)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (-1);
	redir->tag = (t_redir_tag) token->lexeme;
	redir->pathfile = ft_strndup(shell->cmd_line_input + token->i, token->size);
	if (!redir->pathfile)
	{
		free(redir);
		return (-1);
	}
	expression->content = redir;
	return (0);
}

static int	set_expression(t_expression *expression, t_token *token,
	t_shell *shell)
{
	const t_set_expression_content	set_expression_content[] = {NULL, NULL,
		NULL, NULL, NULL, NULL, &set_expression_heredoc, &set_expression_redir,
		&set_expression_redir, &set_expression_redir, &set_expression_redir,
		&set_expression_argument};

	expression->lexeme = token->lexeme;
	expression->content = NULL;
	if (set_expression_content[token->lexeme])
		return ((set_expression_content[token->lexeme])(expression, token,
			shell));
	return (0);
}

int	interpreter_input(t_expression **expressions, t_token *tokens,
	t_shell *shell)
{
	int	i;

	*expressions = malloc(sizeof(t_expression) * count_tokens(tokens));
	if (!*expressions)
		return (-1);
	i = 0;
	while (i < count_tokens(tokens))
		(*expressions)[i++].lexeme = newline;
	i = 0;
	while (tokens[i].lexeme != newline)
	{
		if (set_expression(*expressions + i, tokens + i, shell) == -1)
			return (-1);
		i++;
	}
	if (set_expression(*expressions + i, tokens + i, shell) == -1)
		return (-1);
	return (0);
}
