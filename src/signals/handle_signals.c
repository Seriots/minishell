/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:34:53 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/06 19:49:38 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "../../include/libft.h"
#include "../../include/minishell.h"

/*
* get sigint (Ctrl + C)
*/
int	get_sigint(void)
{
	printf("\n%s", SHELL_PROMPT);
	rl_replace_line("", 0);
	rl_redisplay();
	return (0);
}

/*
*Signal getter, actually small but easy to improve
*/
void	get_sig(int sig, siginfo_t *siginfo, void *context)
{
	(void)siginfo;
	(void)context;
	if (sig == SIGINT)
		get_sigint();
}
