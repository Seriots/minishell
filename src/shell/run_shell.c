/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:59:42 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/01 04:21:09 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include "../../include/libft.h"
#include "../../include/minishell.h"
#include "run_cmd_line.h"

/*
* Check th return value of get_commands and if return is Null, quit the program.
*/
static int	is_exit(t_tree	*commands)
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
	t_tree				*commands;
	struct sigaction	sigact;

	sigact = init_sigact();
	end = 0;
	sigaction(SIGINT, &sigact, NULL);
	sigaction(SIGQUIT, &sigact, NULL);
	while (!end)
	{
		if (read_cmd_line(&commands) == -1)
			return (-1);
		end = is_exit(commands);
		run_cmd_line(commands, shell);
		shell->env_str = dict_to_array(shell->env);
	}
	return (0);
}
