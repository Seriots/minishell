/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeaddtreeback_right.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:43:10 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/06 18:43:46 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_treeaddtreeback_right(t_tree **tree, t_tree *tree_backright)
{
	t_tree	*tree_last_right;

	if (!tree)
		return (-1);
	if (!*tree)
	{
		*tree = tree_backright;
		return (0);
	}
	tree_last_right = ft_treelast_right(*tree);
	tree_last_right->right = tree_backright;
	return (0);
}
