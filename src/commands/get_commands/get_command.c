/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 21:18:04 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/09 17:48:41 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "minishell.h"

t_command	*get_command(const char *input, int input_size)
{
	t_command	*command;

	command = get_bzero_command();
	if (!command)
		return (NULL);
	if (set_redirections(command, input, input_size) == -1)
	{
		free_command(command);
		return (NULL);
	}
	if (set_arguments(command, input, input_size) == -1)
	{
		free_command(command);
		return (NULL);
	}
	return (command);
}
