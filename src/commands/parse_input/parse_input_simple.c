/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_simple.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:48:41 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/09 03:36:44 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include "minishell.h"
#include "tree.h"

t_tree	*parse_input_simple(const char *input, int input_size)
{
	t_command	*command;
	t_tree		*leaf_command;

	command = get_command(input, input_size);
	if (!command)
		return (NULL);
	leaf_command = tree_leafnew(command);
	if (!leaf_command)
	{
		ft_putstr_fd("Error: Creating new leaf of tree failed", 2);
		free_command(command);
		return (NULL);
	}
	return (leaf_command);
}
