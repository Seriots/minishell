/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 22:28:22 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/12 02:09:54 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "cmd_line.h"
#include "read_cmd_line.h"
#include "tree.h"

static int	set_args(t_node *leaf, t_expression *expressions)
{
	char	**args;
	int		args_size;
	int		i;
	int		j;

	args_size = count_lexeme(expressions, argument);
	args = malloc(sizeof(char *) * (args_size + 1));
	if (!args)
		return (-1);
	i = 0;
	j = 0;
	while (expressions[j].lexeme != newline)
	{
		if (expressions[j].lexeme == argument)
			args[i++] = expressions[j].content;
		j++;
	}
	args[i] = NULL;
	leaf->args = args;
	return (0);
}

static int	set_redirs(t_node *leaf, t_expression *expressions)
{
	t_redir	**redirs;
	int		redirs_size;
	int		i;
	int		j;

	redirs_size = get_indice_next_lexeme(expressions, 0, newline)
		- count_lexeme(expressions, argument);
	redirs = malloc(sizeof(t_redir *) * (redirs_size + 1));
	if (!redirs)
		return (-1);
	i = 0;
	j = 0;
	while (expressions[j].lexeme != newline)
	{
		if (expressions[j].lexeme != argument)
			redirs[i++] = expressions[j].content;
		j++;
	}
	redirs[i] = NULL;
	leaf->redirs = redirs;
	return (0);
}

int	parser_args(t_tree **cmd_line, t_expression *expressions)
{
	t_node	*leaf;

	leaf = malloc(sizeof(t_node));
	if (!leaf)
		return (-1);
	leaf->tag = args;
	if (set_args(leaf, expressions) == -1)
		return (free(leaf), -1);
	if (set_redirs(leaf, expressions) == -1)
		return (free(leaf->args), free(leaf), -1);
	*cmd_line = tree_new_leaf(leaf);
	if (!*cmd_line)
		return (free(leaf->args), free(leaf->redirs), free(leaf), -1);
	return (0);
}
