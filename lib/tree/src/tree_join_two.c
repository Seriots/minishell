/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_join_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 21:02:32 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/09 01:21:23 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "list.h"
#include "tree.h"

t_tree	*tree_join_two(t_tree *tree_left, t_tree *tree_right, void *node)
{
	t_list	*childs;
	t_list	*child_left;
	t_list	*child_right;

	child_left = ft_lstnew(tree_left);
	if (!child_left)
		return (NULL);
	child_right = ft_lstnew(tree_right);
	if (!child_right)
	{
		ft_lstclear(&child_left, NULL);
		return (NULL);
	}
	childs = NULL;
	ft_lstadd_front(&childs, child_right);
	ft_lstadd_front(&childs, child_left);
	return (tree_join(childs, node));
}
