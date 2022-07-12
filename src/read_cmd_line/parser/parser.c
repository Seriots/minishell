/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 22:03:43 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/12 02:09:36 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "read_cmd_line.h"
#include "tree.h"

static int	contain_lexeme(t_lexeme lexeme, t_expression *expressions)
{
	int	par_to_close;

	par_to_close = 0;
	while (expressions->lexeme != newline)
	{
		par_to_close += expressions->lexeme == parenthesis_left;
		par_to_close -= expressions->lexeme == parenthesis_right;
		if (par_to_close == 0 && expressions->lexeme == lexeme)
			return (1);
		expressions++;
	}
	return (0);
}

int	parser(t_tree **cmd_line, t_expression *expressions)
{
	*cmd_line = NULL;
	if (contain_lexeme(logical_or, expressions))
		return (parser_or(cmd_line, expressions));
	if (contain_lexeme(logical_and, expressions))
		return (parser_and(cmd_line, expressions));
	if (contain_lexeme(pipe_lexeme, expressions))
		return (parser_pipe(cmd_line, expressions));
	if (contain_lexeme(parenthesis_right, expressions))
		return (parser_parenthesis(cmd_line, expressions));
	return (parser_args(cmd_line, expressions));
}
