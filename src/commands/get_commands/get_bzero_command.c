/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bzero_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 21:33:49 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/10 14:37:32 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

t_command	*get_bzero_command(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
	{
		ft_putstr_fd("Error: malloc command\n", 2);
		return (NULL);
	}
	command->argv = NULL;
	command->std = NULL;
	return (command);
}
