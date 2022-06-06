/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treelast_left.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:01:36 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/06 18:01:51 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

t_tree	*ft_treelast_left(t_tree *tree)
{
	if (!tree)
		return (NULL);
	while (tree->left)
		tree = tree->left;
	return (tree);
}
