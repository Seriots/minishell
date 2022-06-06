/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_and.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 20:33:56 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/06 20:45:42 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include "minishell.h"

static int	set_next_command_and(t_command **command, const char **input,
	int *input_size)
{
	int	size_and;
	int	i;

	if (*input_size == 0)
	{
		*command = NULL;
		return (0);
	}
	size_and = ft_strlen(AND);
	i = 0;
	while (i < *input_size - size_and && ft_strncmp(*input, AND, size_and) != 0)
		i++;
	*command = get_command(*input, i);
	if (!*command)
		return (-1);
	*input += i + size_and;
	*input_size -= i + size_and;
	return (0);
}

static int	init_parse_input_and(t_tree **commands, const char *input,
	int input_size)
{
	t_command	*command;

	if (set_next_command_and(&command, &input, &input_size) == -1)
		return (-1);
	*commands = ft_treeleafnew(command);
	if (!*commands)
	{
		free_command(command);
		return (-1);
	}
	return (0);
}

t_tree	*parse_input_and(const char *input, int input_size)
{
	t_tree		*commands;
	t_command	*command;

	if (init_parse_input_and(&commands, input, input_size) == -1)
		return (NULL);
	while (1)
	{
		if (set_next_command_and(&command, &input, &input_size) == -1)
		{
			ft_treeclear(commands, NULL, free_command);
			return (NULL);
		}
		if (!command)
			break ;
		if (ft_treeaddfront_right(commands, AND, command) == -1)
		{
			free_command(command);
			ft_treeclear(commands, NULL, free_command);
			return (NULL);
		}
	}
	return (commands);
}
