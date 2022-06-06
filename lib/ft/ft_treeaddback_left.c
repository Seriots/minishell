/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeaddback_left.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:17:01 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/06 18:18:40 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_treeaddback_left(t_tree **tree, void *content)
{
	t_tree	*leaf;
	t_tree	*tree_last_left;

	if (!tree)
		return (-1);
	leaf = ft_treeleafnew(content);
	if (!leaf)
		return (-1);
	if (!*tree)
	{
		*tree = leaf;
		return (0);
	}
	tree_last_left = ft_treelast_left(*tree);
	tree_last_left->left = leaf;
	return (0);
}
