/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeaddfront_left.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:02:11 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/06 18:55:43 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

int	ft_treeaddfront_left(t_tree **tree, void *node, void *content)
{
	t_tree	*leaf_left;
	t_tree	*new_tree;

	if (!tree)
		return (-1);
	leaf_left = ft_treeleafnew(content);
	if (!leaf_left)
		return (-1);
	new_tree = ft_treejoin(leaf_left, node, *tree);
	if (!new_tree)
	{
		ft_treeclear(leaf_left, NULL, NULL);
		return (-1);
	}
	*tree = new_tree;
	return (0);
}
