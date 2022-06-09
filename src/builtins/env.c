/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 21:13:03 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/09 02:27:27 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"
#include "../../include/minishell.h"

/*
* Builtins command env, print the content of env (shell->env).
*/
void	env_command(t_shell *shell, char **arguments)
{
	(void)arguments;
	dict_print(shell->env, 0);
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
