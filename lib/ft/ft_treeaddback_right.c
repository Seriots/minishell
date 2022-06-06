/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeaddback_right.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:03:35 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/06 18:19:10 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_treeaddback_right(t_tree **tree, void *content)
{
	t_tree	*leaf;
	t_tree	*tree_last_right;

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
	tree_last_right = ft_treelast_right(*tree);
	tree_last_right->right = leaf;
	return (0);
}
