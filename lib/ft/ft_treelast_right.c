/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treelast_right.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:59:54 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/06 18:01:05 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

t_tree	*ft_treelast_right(t_tree *tree)
{
	if (!tree)
		return (NULL);
	while (tree->right)
		tree = tree->right;
	return (tree);
}
