/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 01:02:34 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/07 15:17:52 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

int	set_arguments(t_command *cmd, const char *input, int input_size)
{
	int	argc;
	int	i_arg;
	int	i;

	argc = count_arguments(input, input_size);
	argc -= 2 * count_redirections(input, input_size);
	cmd->argv = malloc(sizeof(char *) * (argc + 1));
	if (!cmd->argv)
	{
		perror("Error: malloc command arguments");
		return (-1);
	}
	i = 0;
	skip_whitespaces(input, input_size, &i);
	i_arg = 0;
	while (i_arg < argc)
	{
		skip_redirections(input, input_size, &i);
		cmd->argv[i_arg] = get_argument(input, input_size, i);
		if (!cmd->argv[i_arg])
			return (-1);
		skip_to_next_argument(input, input_size, &i);
		i_arg++;
	}
	return (0);
}
