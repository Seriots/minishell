/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 22:18:25 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/12 03:01:13 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "shell.h"

extern t_shell_status	g_shell_status;

int	exit_command(t_shell *shell, char **arguments)
{
	(void) shell;
	g_shell_status = terminating_shell;
	if (arguments[0] != 0)
		return (ft_atoi(arguments[0]));
	return (0);
}
