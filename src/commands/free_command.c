/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:05:21 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/07 15:14:35 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

void	free_command(void *command_addr)
{
	t_command	*command;

	command = (t_command *) command_addr;
	if (!command)
		return ;
	if (command->exec_path)
		free(command->exec_path);
	if (command->argv)
		ft_free_tab(command->argv);
	if (command->pathfile_stdin)
		free(command->pathfile_stdin);
	if (command->end_heredoc)
		free(command->end_heredoc);
	if (command->pathfile_stdout)
		free(command->pathfile_stdout);
	free(command);
}
