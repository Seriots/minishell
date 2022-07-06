/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 22:42:20 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/06 04:56:56 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include "../../include/checker.h"
#include "../../include/lexer.h"
#include "../../include/libft.h"
#include "../../include/minishell.h"
#include "../../include/read_cmd_line.h"
#include "../../include/tree.h"

extern int	g_stop_run;

static void	free_expressions(t_expression *expressions)
{
	int	i;

	if (!expressions)
		return ;
	while (expressions[i].lexeme != newline)
	{
		if (expressions[i].lexeme >= redir_heredoc)
			free_cmd_line(expressions[i].content);
		i++;
	}
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
	free(expressions);
	return (ret_value);
}

int	read_cmd_line(t_tree **cmd_line)
{
	char	*input;
	int		ret_value;

	stop_run = 0;
	input = readline(PROMPT_SHELL);
	if (stop_run == 0)
		stop_run = 1;
	else
		stop_run = 3;
	if (!input)
		return (-2);
	if (!ft_strlen(input))
		return (-3);
	add_history(input);
	ret_value = set_cmd_line(input, cmd_line);
	free(input);
	return (ret_value);
}
