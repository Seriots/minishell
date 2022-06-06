/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 20:34:45 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/06 20:46:41 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include "minishell.h"

static int	set_next_command_pipe(t_command **command, const char **input,
	int *input_size)
{
	int	size_pipe;
	int	i;

	if (*input_size == 0)
	{
		*command = NULL;
		return (0);
	}
	size_pipe = ft_strlen(PIPE);
	i = 0;
	while (i < *input_size - size_pipe
		&& ft_strncmp(*input, PIPE, size_pipe) != 0)
		i++;
	*command = get_command(*input, i);
	if (!*command)
		return (-1);
	*input += i + size_pipe;
	*input_size -= i + size_pipe;
	return (0);
}

static int	init_parse_input_pipe(t_tree **commands, const char *input,
	int input_size)
{
	t_command	*command;

	if (set_next_command_pipe(&command, &input, &input_size) == -1)
		return (-1);
	*commands = ft_treeleafnew(command);
	if (!*commands)
	{
		free_command(command);
		return (-1);
	}
	return (0);
}

t_tree	*parse_input_pipe(const char *input, int input_size)
{
	t_tree		*commands;
	t_command	*command;

	if (init_parse_input_pipe(&commands, input, input_size) == -1)
		return (NULL);
	while (1)
	{
		if (set_next_command_pipe(&command, &input, &input_size) == -1)
		{
			ft_treeclear(commands, NULL, free_command);
			return (NULL);
		}
		if (!command)
			break ;
		if (ft_treeaddfront_right(commands, PIPE, command) == -1)
		{
			free_command(command);
			ft_treeclear(commands, NULL, free_command);
			return (NULL);
		}
	}
	return (commands);
}
