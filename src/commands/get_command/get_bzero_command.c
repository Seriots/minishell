/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bzero_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 21:33:49 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/07 00:45:17 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "minishell.h"

t_command	*get_bzero_command(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->exec_path = NULL;
	command->argv = NULL;
	command->redir_stdin = 0;
	command->pathfile_stdin = NULL;
	command->heredoc_stdin = 0;
	command->end_heredoc = NULL;
	command->redir_stdout = 0;
	command->redir_append_stdout = 0;
	command->pathfile_stdout = NULL;
	return (command);
}
