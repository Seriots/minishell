/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:38:57 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/06 18:56:34 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_treeclear(t_tree *tree, void (*del_node)(void *),
	void (*del_leaf)(void *))
{
	if (!tree)
		return ;
	if (!tree->left && !tree->right)
	{
		if (*del_leaf)
			(*del_leaf)(tree->content);
		return ;
	}
	if (tree->left)
		ft_treeclear(tree->left, *del_node, *del_leaf);
	if (*del_node)
		(*del_node)(tree->content);
	if (tree->right)
		ft_treeclear(tree->right, *del_node, *del_leaf);
}
