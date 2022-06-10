/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:40:40 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/09 17:40:59 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "list.h"
#include "minishell.h"
#include "tree.h"

static t_tree	*get_command_pipe(const char *input, int input_size, int *i)
{
	t_tree	*command;
	int		j;

	j = *i;
	skip_to(PIPE, input, input_size, &j);
	command = parse_input(input + *i, input_size - (j - *i));
	skip_to_next_argument(input, input_size, &j);
	*i = j;
	return (command);
}

t_tree	*parse_input_pipe(const char *input, int input_size)
{
	t_tree		*tree;
	t_list		*sub_commands;
	t_tree		*command;
	int			i;

	sub_commands = NULL;
	i = 0;
	while (i < input_size)
	{
		command = get_command_pipe(input, input_size, &i);
		if (!command || list_append(&sub_commands, command) == -1)
		{
			if (command)
				free_command(command);
			list_clear(sub_commands, free_command);
			return (NULL);
		}
	}
	tree = tree_join(sub_commands, PIPE);
	if (!tree)
		list_clear(sub_commands, free_command);
	return (tree);
}
