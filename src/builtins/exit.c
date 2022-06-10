/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 22:18:25 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/10 22:27:20 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/dict.h"
#include "../../include/libft.h"
#include "../../include/ft_printf.h"
#include "../../include/minishell.h"
#include <stdlib.h>

int	exit_command(t_shell *shell, char **arguments)
{
	(void)arguments;
	free_shell (shell);
	ft_printf("exit\n");
	exit (0);
	return (0);
}

int	main(int argc, char *argv[], char **env)
{
	t_shell	shell;

	init_shell(&shell, env);
	argv = &argv[1];
	exit_command(&shell, argv);
	dict_print(shell.env, 0);
	free_shell(&shell);
}
