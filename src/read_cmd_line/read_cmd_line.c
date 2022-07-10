/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 22:42:20 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/10 22:45:40 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include "checker.h"
#include "cmd_line.h"
#include "lexer.h"
#include "libft.h"
#include "read_cmd_line.h"
#include "shell.h"
#include "tree.h"

extern t_shell_status	g_shell_status;

void	set_input(const char *prompt, t_shell *shell)
{
	shell->input = readline(prompt);
	if (!shell->input && g_shell_status == reading_cmd_line)
		g_shell_status = terminating_shell;
}

static void	free_expressions(t_expression *expressions)
{
	int	i;

	if (!expressions)
		return ;
	i = 0;
	while (expressions[i].lexeme && expressions[i].lexeme != newline)
	{
		if (expressions[i].lexeme >= redir_heredoc)
			free_cmd_line(expressions[i].content);
		i++;
	}
}

static int	set_cmd_line(t_tree **cmd_line, t_shell *shell)
{
	t_token			*tokens;
	t_expression	*expressions;
	int				ret_value;

	tokens = NULL;
	expressions = NULL;
	*cmd_line = NULL;
	ret_value = 0;
	if (lexer(&tokens, shell->input) == -1
		|| checker(tokens, shell->input) == -1
		|| interpreter_input(&expressions, tokens, shell) == -1
		|| parser(cmd_line, expressions) == -1)
		ret_value = -1;
	free(tokens);
	if (!*cmd_line)
		free_expressions(expressions);
	free(expressions);
	return (ret_value);
}

int	read_cmd_line(t_tree **cmd_line, t_shell *shell)
{
	int		ret_value;

	g_shell_status = reading_cmd_line;
	set_input(PROMPT_SHELL, shell);
	if (g_shell_status == terminating_shell)
		return (0);
	while (g_shell_status == reading_cmd_line)
	{
		add_history(shell->input);
		g_shell_status = parsing_cmd_line;
		ret_value = set_cmd_line(cmd_line, shell);
		if (g_shell_status == reading_cmd_line)
			shell->return_value = 130;
	}
	free(shell->input);
	shell->input = NULL;
	return (ret_value);
}
