/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:59:42 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/06 19:49:18 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include "../../include/libft.h"
#include "../../include/minishell.h"

/*
* Check th return value of get_commands and if return is Null, quit the program.
*/
static int	is_exit(char **commands)
{
	if (commands)
		return (0);
	printf("exit\n");
	return (1);
}

/*
* Main loop to read user input in the shell
*/
int	run_shell(t_shell *shell)
{
	int					end;
	char				**commands;
	struct sigaction	sigact;

	sigact = init_sigact();
	end = 0;
	sigaction(SIGINT, &sigact, NULL);
	sigaction(SIGQUIT, &sigact, NULL);
	while (!end)
	{
		commands = get_commands(shell);
		end = is_exit(commands);
		run_commands(commands, shell);
	}
	return (0);
}
