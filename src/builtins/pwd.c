/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:25:34 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/07 18:09:14 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "../../include/minishell.h"

/*
* pwd builtin command, IDK if a '\n' is needed.
*/
void	pwd_command(t_shell *shell, char **arguments)
{
	(void)arguments;
	/*if (!arguments)
		return ;
	if (arguments[0] == 0)*/
	write(1, shell->directory, ft_strlen(shell->directory));
	/*else
		write (1, "pwd: too many arguments", 24);
	write (1, "\n", 1);*/
}

int	main(int argc, char *argv[])
{
	t_shell	shell;

	init_shell(&shell, 0);
	argv = &argv[1];
	pwd_command(&shell, argv);
}