/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treedepth.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:34:15 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/06 18:56:48 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_treedepth(t_tree *tree)
{
	int	depth_left;
	int	depth_right;

	if (!tree)
		return (0);
	depth_left = ft_treedepth(tree->left);
	depth_right = ft_treedepth(tree->right);
	if (depth_left > depth_right)
		return (depth_left + 1);
	return (depth_right + 1);
}
