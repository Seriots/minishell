/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_parenthesis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 01:21:58 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/09 22:04:40 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_cmd_line.h"
#include "tree.h"

int	parser_parenthesis(t_tree **cmd_line, t_expression *expressions)
{
	int	i;
	int	ret_value;

	i = get_indice_next_lexeme(expressions, 0, parenthesis_right);
	expressions[i].lexeme = newline;
	ret_value = parser(cmd_line, expressions + 1);
	expressions[i].lexeme = parenthesis_right;
	return (ret_value);
}
