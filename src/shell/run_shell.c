/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:59:42 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/04 22:51:58 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include "../../include/libft.h"
#include "../../include/minishell.h"
#include "../../include/run_cmd_line.h"

/*
* Check th return value of get_commands and if return is Null, quit the program.
*/
/*
* Main loop to read user input in the shell
*/
int	run_shell(t_shell *shell)
{
	int					end;
	t_tree				*commands;
	struct sigaction	sigact;
	int					ret_value;

	sigact = init_sigact();
	end = 0;
	sigaction(SIGINT, &sigact, NULL);
	sigaction(SIGQUIT, &sigact, NULL);
	while (!end)
	{
		ret_value = read_cmd_line(&commands);
		if (ret_value == -1)
			return (-1);
		else if (ret_value == -2)
			return (printf("exit\n"), -1);
		run_cmd_line(commands, shell);
		shell->env_str = dict_to_array(shell->env);
	}
	return (0);
}
