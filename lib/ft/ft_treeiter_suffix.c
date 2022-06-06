/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeiter_suffix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:31:29 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/06 18:57:12 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_treeiter_suffix(t_tree *tree, void (*f_node)(void *),
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
	if (tree->left)
		ft_treeiter_suffix(tree->left, *f_node, *f_leaf);
	if (tree->right)
		ft_treeiter_suffix(tree->right, *f_node, *f_leaf);
	if (tree->content)
		(*f_node)(tree->content);
}
