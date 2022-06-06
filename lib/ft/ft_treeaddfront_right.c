/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeaddfront_right.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:46:01 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/06 18:55:55 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

int	ft_treeaddfront_right(t_tree **tree, void *node, void *content)
{
	t_tree	*leaf_right;
	t_tree	*new_tree;

	if (!tree)
		return (-1);
	leaf_right = ft_treeleafnew(content);
	if (!leaf_right)
		return (-1);
	new_tree = ft_treejoin(*tree, node, leaf_right);
	if (!new_tree)
	{
		ft_treeclear(leaf_right, NULL, NULL);
		return (-1);
	}
	*tree = new_tree;
	return (0);
}
