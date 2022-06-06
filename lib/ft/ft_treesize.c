/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treesize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:24:48 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/06 18:25:51 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_treesize(t_tree *tree)
{
	int	size;

	if (!tree)
		return (0);
	size = ft_treesize(tree->left);
	size += 1;
	size = ft_treesize(tree->right);
	return (size);
}
