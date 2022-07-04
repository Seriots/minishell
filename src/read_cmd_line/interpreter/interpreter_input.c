/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 23:09:56 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/04 22:33:02 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "read_cmd_line.h"

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
	const char *input)
{
	expression->content = ft_strndup(input + token->i, token->size);
	if (!expression->content)
		return (-1);
	return (0);
}

static int	set_expression_redir(t_expression *expression, t_token *token,
	const char *input)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (-1);
	redir->tag = (t_redir_tag) token->lexeme;
	redir->pathfile = ft_strndup(input + token->i, token->size);
	if (!redir->pathfile)
	{
		free(redir);
		return (-1);
	}
	expression->content = redir;
	return (0);
}

static int	set_expression(t_expression *expression, t_token *token,
	const char *input)
{
	const t_set_expression_content	set_expression_content[] = {NULL, NULL,
		NULL, NULL, NULL, NULL, &set_expression_heredoc, &set_expression_redir,
		&set_expression_redir, &set_expression_redir, &set_expression_redir,
		&set_expression_argument};

	expression->lexeme = token->lexeme;
	expression->content = NULL;
	if (set_expression_content[token->lexeme])
		return ((set_expression_content[token->lexeme])(expression, token,
			input));
	return (0);
}

int	interpreter_input(t_expression **expressions, t_token *tokens,
	const char *input)
{
	int	i;

	*expressions = malloc(sizeof(t_expression) * count_tokens(tokens));
	if (!*expressions)
		return (-1);
	i = 0;
	while (tokens[i].lexeme != newline)
	{
		(*expressions)[i].lexeme = newline;
		if (set_expression(*expressions + i, tokens + i, input) == -1)
			return (-1);
		i++;
	}
	if (set_expression(*expressions + i, tokens + i, input) == -1)
		return (-1);
	return (0);
}
