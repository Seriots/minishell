/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 20:45:57 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/12 02:05:51 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cmd_line.h"
#include "read_cmd_line.h"
#include "tree.h"

static int	set_node_pipe(t_tree **cmd_line)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (-1);
	node->tag = pipeline;
	*cmd_line = tree_new_leaf(node);
	if (!*cmd_line)
		return (free(node), -1);
	return (0);
}

static int	add_pipeline(t_tree *cmd_line, t_expression *expressions)
{
	t_tree	*cmd_pipe;
	int		ret_value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i != 0 || j == 0)
	{
		j = get_indice_next_lexeme(expressions, i, pipe_lexeme);
		if (j != -1)
			expressions[j].lexeme = newline;
		ret_value = parser(&cmd_pipe, expressions + i);
		if (j != -1)
			expressions[j].lexeme = pipe_lexeme;
		if (ret_value == -1 || tree_adopt(cmd_line, cmd_pipe) == -1)
			return (tree_clear(cmd_pipe, &free_cmd_line_struct), -1);
		i = j + 1;
	}
	return (0);
}

int	parser_pipe(t_tree **cmd_line, t_expression *expressions)
{
	if (set_node_pipe(cmd_line) == -1)
		return (-1);
	if (add_pipeline(*cmd_line, expressions) == -1)
		return (-1);
	return (0);
}
