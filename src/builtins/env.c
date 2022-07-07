/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 21:13:03 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/07 03:00:13 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dict.h"
#include "minishell.h"

/*
* Builtins command env, print the content of env (shell->env).
*/
int	env_command(t_shell *shell, char **arguments)
{
	(void)arguments;
	if (!shell || !shell->env)
		return (1);
	dict_print(shell->env, 0);
	return (0);
}

/*
int	main(int argc, char *argv[], char **env)
{
	t_shell	shell;

	init_shell(&shell, env);
	argv = &argv[1];
	env_command(&shell, argv);
}
*/
