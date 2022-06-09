/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_or.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 03:47:40 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/09 04:42:15 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "list.h"
#include "minishell.h"
#include "tree.h"

t_tree	*parse_input_or(const char *input, int input_size)
{
	t_tree		*tree;
	t_list		*sub_commands;
	t_command	*command;
	int			i;

	sub_commands = NULL;
	i = 0;
	while (i < input_size)
	{
		command = get_command(input, input_size, &i);
		if (!command || list_append() == -1)
		{
			if (command)
				free_command(command);
			list_clear(sub_commands, free_commands);
			return (NULL);
		}
	}
	tree = tree_join(sub_commands, OR);
	if (!tree)
		list_clear(sub_commands, free_command);
	return (tree);
}
