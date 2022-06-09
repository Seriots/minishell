/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 21:09:55 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/08 21:13:18 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tree.h"

void	tree_clear(t_tree *tree, void (*free_node)(void *),
	void (*free_leaf)(void *))
{
	if (!tree)
		return ;
	if (!tree->childs)
	{
		if (*free_leaf)
			(*free_leaf)(tree->content);
		return ;
	}
	if (*free_node)
		(*free_node)(tree->content);
	while (tree->childs)
	{
		tree_clear(tree->childs->content, free_node, free_leaf);
		tree->childs = tree->childs->next;
	}
	free(tree);
}
