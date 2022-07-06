/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:34:53 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/06 05:15:51 by rgarrigo         ###   ########.fr       */
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
#include "../../include/ft_printf.h"

extern int	g_stop_run;

/*
* get sigint (Ctrl + C)
*/
int	get_sigint(void)
{
	if (stop_run == 0 || stop_run == 2)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("\n");
		rl_redisplay();
		stop_run = 2;
	}
	else if (stop_run == 1 || stop_run == 3)
	{
		stop_run = 4;
		printf("\n");
	}
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
