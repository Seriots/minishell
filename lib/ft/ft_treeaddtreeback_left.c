/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeaddtreeback_left.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:24:20 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/06 18:24:33 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_treeaddtreeback_left(t_tree **tree, t_tree *tree_backleft)
{
	t_tree	*tree_last_left;

	if (!tree)
		return (-1);
	if (!*tree)
	{
		*tree = tree_backleft;
		return (0);
	}
	tree_last_left = ft_treelast_left(*tree);
	tree_last_left->left = tree_backleft;
	return (0);
}
