/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeiter_prefix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:26:19 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/06 18:57:07 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_treeiter_prefix(t_tree *tree, void (*f_node)(void *),
	void (*f_leaf)(void *))
{
	if (!tree)
		return ;
	if (!tree->left && !tree->right)
	{
		if (*f_leaf)
			(*f_leaf)(tree->content);
		return ;
	}
	if (tree->content)
		(*f_node)(tree->content);
	if (tree->left)
		ft_treeiter_prefix(tree->left, *f_node, *f_leaf);
	if (tree->right)
		ft_treeiter_prefix(tree->right, *f_node, *f_leaf);
}
