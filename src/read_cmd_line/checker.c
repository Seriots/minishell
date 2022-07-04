/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 21:07:00 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/04 22:49:07 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include "read_cmd_line.h"

int	checker_error(const char *input, int i)
{
	(void) input;
	(void) i;
	return (-1);
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
			return (checker_error(input, tokens[i].i));
		update_forbidden(&forbidden, tokens[i].lexeme);
		par_to_close += (tokens[i].lexeme == parenthesis_left);
		par_to_close -= (tokens[i].lexeme == parenthesis_right);
		if (par_to_close < 0)
			return (checker_error(input, tokens[i].i));
		i++;
	}
	if (forbidden & 1 << tokens[i].lexeme || par_to_close != 0)
		return (checker_error(input, tokens[i].i));
	return (0);
}
