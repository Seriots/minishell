/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:34:50 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/07 03:23:41 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "minishell.h"

int	main(int argc, char *argv[], char **env)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	if (init_shell(&shell, env) == -1)
		return (1);
	run_shell(&shell);
	rl_clear_history();
	free_shell(&shell);
	return (0);
}
