/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 21:09:55 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/01 04:03:36 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tree.h"

void	tree_clear(t_tree *tree, void (*free_node)(void *))
{
	if (!tree)
		return ;
	if (*free_node)
		(*free_node)(tree->content);
	while (tree->childs)
	{
		tree_clear(tree->childs->content, free_node);
		tree->childs = tree->childs->next;
	}
	free(tree);
}
