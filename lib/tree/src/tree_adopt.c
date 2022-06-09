/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_adopt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 21:29:18 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/09 01:21:22 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "tree.h"

int	tree_adopt(t_tree *parent, t_tree *child)
{
	t_list	*child_l;

	child_l = ft_lstnew(child);
	if (!child_l)
		return (-1);
	ft_lstadd_front(&parent->childs, child_l);
	return (0);
}
