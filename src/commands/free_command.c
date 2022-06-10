/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:37:58 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/10 15:23:37 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "list.h"
#include "minishell.h"

void	free_argv(void *argv_addr)
{
	char	**argv;
	int		i;

	if (!argv_addr)
		return ;
	argv = (char **) argv_addr;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_std(void *std_addr)
{
	t_std	*std;

	if (!std_addr)
		return ;
	std = (t_std *) std_addr;
	if (std->fd)
		close(std->fd);
	if (std->pathfile)
		free(std->pathfile);
	if (std->end)
		free(std->end);
	free(std);
}

void	free_command(void *command_addr)
{
	t_command	*command;

	if (!command_addr)
		return ;
	command = (t_command *) command_addr;
	if (command->argv)
		free_argv(command->argv);
	if (command->std)
		list_clear(&command->std, free_std);
	free(command);
}
