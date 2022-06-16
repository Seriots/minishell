/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:34:50 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/15 13:57:33 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../include/minishell.h"

int	main(int argc, char *argv[], char **env)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	if (init_shell(&shell, env) == -1)
		return (1);
	run_shell(&shell);
	free_shell(&shell);
	return (0);
}
