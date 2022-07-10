/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_or.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 03:38:44 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/10 21:43:49 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cmd_line.h"
#include "read_cmd_line.h"
#include "tree.h"

static int	set_node_or(t_tree **cmd_line)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (-1);
	node->tag = list_or;
	*cmd_line = tree_new_leaf(node);
	if (!*cmd_line)
		return (free(node), -1);
	return (0);
}

static int	add_list_or(t_tree *cmd_line, t_expression *expressions)
{
	t_tree	*cmd_or;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i != 0 || j == 0)
	{
		j = get_indice_next_lexeme(expressions, i, logical_or);
		if (j != -1)
			expressions[j].lexeme = newline;
		if (parser(&cmd_or, expressions + i) == -1)
			return (-1);
		if (j != -1)
			expressions[j].lexeme = logical_or;
		if (tree_adopt(cmd_line, cmd_or) == -1)
			return (tree_clear(cmd_or, &free_cmd_line), -1);
		i = j + 1;
	}
	return (0);
}

int	parser_or(t_tree **cmd_line, t_expression *expressions)
{
	if (set_node_or(cmd_line) == -1)
		return (-1);
	if (add_list_or(*cmd_line, expressions) == -1)
		return (tree_clear(*cmd_line, &free_cmd_line), -1);
	return (0);
}
