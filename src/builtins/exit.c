/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 22:18:25 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/13 01:12:56 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "shell.h"

extern t_shell_status	g_shell_status;

static void	manage_error_exit_argument(const char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

int	exit_command(t_shell *shell, char **arguments)
{
	int	ret_value;

	if (g_shell_status != running_subshell_cmd_line)
		ft_putstr_fd("exit\n", 2);
	ret_value = shell->return_value;
	if (arguments[0] != 0)
	{
		if (!ft_islong(arguments[0]))
		{
			manage_error_exit_argument(arguments[0]);
			ret_value = 2;
		}
		else
		{
			ret_value = ft_atoi(arguments[0]);
			ret_value %= 256;
			if (ret_value < 0)
				ret_value += 256;
		}
	}
	g_shell_status = terminating_shell;
	return (ret_value);
}
