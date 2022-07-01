/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 22:42:20 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/01 04:16:00 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include "checker.h"
#include "lexer.h"
#include "minishell.h"
#include "read_cmd_line.h"
#include "tree.h"

static void	free_expressions(t_expression *expressions)
{
	int	i;

	while (expressions[i].lexeme != newline)
	{
		if (expressions[i].lexeme >= redir_heredoc)
			free_cmd_line(expressions[i].content);
		i++;
	}
	free(expressions);
}

static int	set_cmd_line(const char *input, t_tree **cmd_line)
{
	t_token			*tokens;
	t_expression	*expressions;
	int				ret_value;

	tokens = NULL;
	expressions = NULL;
	*cmd_line = NULL;
	ret_value = 0;
	if (lexer(input, &tokens) == -1
		|| checker(tokens, input) == -1
		|| interpreter_input(&expressions, tokens, input) == -1
		|| parser(cmd_line, expressions) == -1)
		ret_value = -1;
	free(tokens);
	if (!*cmd_line)
		free_expressions(expressions);
	return (ret_value);
}

int	read_cmd_line(t_tree **cmd_line)
{
	char	*input;
	int		ret_value;

	input = readline(PROMPT_SHELL);
	if (!input)
		return (-1);
	add_history(input);
	ret_value= set_cmd_line(input, cmd_line);
	free(input);
	return (ret_value);
}
