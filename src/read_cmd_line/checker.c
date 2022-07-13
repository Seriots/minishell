/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 21:07:00 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/13 23:40:07 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include "lexer.h"
#include "libft.h"
#include "read_cmd_line.h"

int	checker_error(t_lexeme lexeme)
{
	const char	*lexeme_str[] = {"newline", PARENTHESIS_LEFT_STR,
		PARENTHESIS_RIGHT_STR, LOGICAL_OR_STR, LOGICAL_AND_STR, PIPE_STR,
		REDIR_HEREDOC_STR, REDIR_STDIN_STR, REDIR_APPEND_STDOUT_STR,
		REDIR_STDOUT_STR, REDIR_STDERR_STR, ARGUMENT_STR};

	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(lexeme_str[lexeme], 2);
	ft_putstr_fd("'\n", 2);
	return (2);
}

void	update_forbidden(int *forbidden, t_lexeme lexeme)
{
	const int	allowed_lex[] = {ALLOWED_NEWLINE, ALLOWED_PAR_LEFT,
		ALLOWED_PAR_RIGHT, ALLOWED_OR, ALLOWED_AND, ALLOWED_PIPE,
		ALLOWED_RED_HEREDOC, ALLOWED_RED_STDIN, ALLOWED_RED_APPEND_STDOUT,
		ALLOWED_RED_STDOUT, ALLOWED_RED_STDERR, ALLOWED_ARGUMENT};
	const int	forbidden_lex[] = {FORBIDDEN_NEWLINE, FORBIDDEN_PAR_LEFT,
		FORBIDDEN_PAR_RIGHT, FORBIDDEN_OR, FORBIDDEN_AND, FORBIDDEN_PIPE,
		FORBIDDEN_RED_HEREDOC, FORBIDDEN_RED_STDIN, FORBIDDEN_RED_APPEND_STDOUT,
		FORBIDDEN_RED_STDOUT, FORBIDDEN_RED_STDERR, FORBIDDEN_ARGUMENT};

	*forbidden &= ~allowed_lex[lexeme];
	*forbidden |= forbidden_lex[lexeme];
}

int	checker(t_token *tokens, const char *input)
{
	int	forbidden;
	int	par_to_close;
	int	i;

	if (!tokens || !input)
		return (-1);
	forbidden = FORBIDDEN_INIT;
	par_to_close = 0;
	i = 0;
	while (tokens[i].lexeme != newline)
	{
		if (forbidden & 1 << tokens[i].lexeme)
			return (checker_error(tokens[i].lexeme), 2);
		update_forbidden(&forbidden, tokens[i].lexeme);
		par_to_close += (tokens[i].lexeme == parenthesis_left);
		par_to_close -= (tokens[i].lexeme == parenthesis_right);
		if (par_to_close < 0)
			return (checker_error(tokens[i].lexeme), 2);
		i++;
	}
	if (forbidden & 1 << tokens[i].lexeme || par_to_close != 0)
		return (checker_error(tokens[i].lexeme), 2);
	return (0);
}
