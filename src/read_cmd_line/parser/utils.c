/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 22:20:22 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/05 01:37:54 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_cmd_line.h"
#include "tree.h"

int	get_indice_next_lexeme(t_expression *expressions, int i, t_lexeme lexeme)
{
	int	par_to_close;

	par_to_close = 0;
	while (expressions[i].lexeme != newline)
	{
		par_to_close += expressions[i].lexeme == parenthesis_left;
		par_to_close -= expressions[i].lexeme == parenthesis_right;
		if (par_to_close == 0 && expressions[i].lexeme == lexeme)
			return (i);
		i++;
	}
	if (lexeme == newline)
		return (i);
	return (-1);
}

int	count_lexeme(t_expression *expressions, t_lexeme lexeme)
{
	int	count;
	int	par_to_close;

	count = 0;
	par_to_close = 0;
	while (expressions->lexeme != newline)
	{
		par_to_close += expressions->lexeme == parenthesis_left;
		par_to_close -= expressions->lexeme == parenthesis_right;
		if (par_to_close == 0 && expressions->lexeme == lexeme)
			count++;
		expressions++;
	}
	return (count);
}
