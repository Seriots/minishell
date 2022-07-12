/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:34:50 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/12 16:36:46 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "shell.h"

int	main(int argc, char *argv[], char **env)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	if (init_shell(&shell, env) == -1)
		return (free_shell(&shell), 1);
	run_shell(&shell);
	rl_clear_history();
	free_shell(&shell);
	return (shell.return_value);
}
