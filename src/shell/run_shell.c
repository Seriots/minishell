/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:59:42 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/08 11:36:24 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stddef.h>
#include "libft.h"
#include "minishell.h"
#include "read_cmd_line.h"
#include "run_cmd_line.h"
#include "tree.h"

/*
* 0=read
* 1=exec
* 2=ctrl+c in read
* 3=ctrl+c in lecture + exec
* 4=ctrl+c in exec
* 5=ctrl+c in child
*/
int	g_stop_run = 0;

/*
* Main loop to read user input in the shell
*/
void	end_cmd_line(t_shell *shell, t_tree *commands, int ret_value, int *end)
{
	tree_clear(commands, &free_cmd_line);
	ft_free_tab(shell->env_str);
	shell->env_str = dict_to_array(shell->env);
	if (g_stop_run == 4)
		shell->return_value = 130;
	else if (ret_value == -2)
	{
		*end = 1;
		ft_putstr_fd("exit\n", 2);
		shell->return_value = 0;
	}
	else
		shell->return_value = ret_value;
}

void	init_run_var(int *end, struct sigaction *sigact)
{
	*end = 0;
	*sigact = init_sigact();
	sigact->sa_handler = SIG_IGN;
	sigaction(SIGQUIT, sigact, NULL);
	sigact->sa_handler = &get_sig;
}

int	run_shell(t_shell *shell)
{
	struct sigaction	sigact;
	t_tree				*commands;
	int					end;
	int					ret_value;

	init_run_var(&end, &sigact);
	while (!end)
	{
		sigaction(SIGINT, &sigact, NULL);
		ret_value = read_cmd_line(&commands);
		if (g_stop_run == 2 || g_stop_run == 3)
				shell->return_value = 130;
		if (ret_value == -1)
			return (-1);
		else if (ret_value == -2)
			return (ft_putstr_fd("exit\n", 2), -1);
		else if (ret_value != -3)
		{
			ret_value = run_cmd_line(commands, shell);
			end_cmd_line(shell, commands, ret_value, &end);
		}
	}
	return (0);
}
