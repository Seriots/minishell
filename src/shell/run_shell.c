/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:59:42 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/13 01:37:16 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stddef.h>
#include "libft.h"
#include "shell.h"
#include "signals.h"
#include "read_cmd_line.h"
#include "run_cmd_line.h"
#include "tree.h"

int	g_shell_status;

/*
* Main loop to read user input in the shell
*/
static void	end_cmd_line(t_shell *shell, t_tree *commands, int ret_value)
{
	tree_clear(commands, &free_cmd_line);
	ft_free_tab(shell->env_str);
	shell->env_str = dict_to_array(shell->env);
	if (!shell->env_str)
		g_shell_status = terminating_shell;
	if (g_shell_status == running_cmd_line)
		shell->return_value = ret_value;
	if (g_shell_status == reading_cmd_line)
		shell->return_value = 130;
	if (g_shell_status == terminating_shell)
		shell->return_value = ret_value;
}

int	run_shell(t_shell *shell)
{
	t_tree				*commands;
	int					ret_value;

	g_shell_status = reading_cmd_line;
	while (g_shell_status != terminating_shell)
	{
		ret_value = read_cmd_line(&commands, shell);
		if (ret_value == -1)
			return (-1);
		if (ret_value == 2)
		{
			shell->return_value = 2;
			continue ;
		}
		if (g_shell_status == terminating_shell)
			break ;
		g_shell_status = running_cmd_line;
		ret_value = run_cmd_line(commands, shell);
		if (ret_value == -1)
			return (tree_clear(commands, &free_cmd_line), -1);
		end_cmd_line(shell, commands, ret_value);
	}
	return (0);
}
