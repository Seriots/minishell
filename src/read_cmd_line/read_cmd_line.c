/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 22:42:20 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/13 16:53:39 by rgarrigo         ###   ########.fr       */
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
	{
		ft_putstr_fd("exit\n", 2);
		g_shell_status = terminating_shell;
	}
}

static void	free_expressions(t_expression *expressions)
{
	int	i;

	if (!expressions)
		return ;
	i = 0;
	while (expressions[i].lexeme && expressions[i].lexeme != newline)
	{
		if (expressions[i].lexeme == argument)
			free(expressions[i].content);
		else if (expressions[i].lexeme >= redir_heredoc)
			free_redir(expressions[i].content);
		i++;
	}
	free(expressions);
}

static int	set_cmd_line(t_tree **cmd_line, t_shell *shell)
{
	t_token			*tokens;
	t_expression	*expressions;
	int				ret_value;

	tokens = NULL;
	expressions = NULL;
	*cmd_line = NULL;
	ret_value = lexer(&tokens, shell->input);
	if (ret_value != 0)
		return (free(tokens), ret_value);
	ret_value = checker(tokens, shell->input);
	if (ret_value != 0)
		return (free(tokens), ret_value);
	if (interpreter_input(&expressions, tokens, shell) == -1
		|| parser(cmd_line, expressions) == -1)
		ret_value = -1;
	free(tokens);
	if (ret_value == -1)
		return (free_expressions(expressions),
			tree_clear(*cmd_line, &free_cmd_line_struct),
			-1);
	free(expressions);
	return (0);
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
		shell->cmd_line_input = shell->input;
		add_history(shell->cmd_line_input);
		g_shell_status = parsing_cmd_line;
		ret_value = set_cmd_line(cmd_line, shell);
		if (g_shell_status == reading_cmd_line)
			shell->return_value = 130;
	}
	free(shell->cmd_line_input);
	return (ret_value);
}
