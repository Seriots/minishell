/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:34:53 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/10 22:40:05 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include "libft.h"
#include "read_cmd_line.h"
#include "shell.h"

extern t_shell_status	g_shell_status;

/*
* get sigint (Ctrl + C)
*/
int	get_sigint(void)
{
	if (g_shell_status == reading_cmd_line)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("\n");
		rl_redisplay();
	}
	if (g_shell_status == parsing_cmd_line)
	{
		g_shell_status = reading_cmd_line;
		rl_replace_line("", 0);
		rl_set_prompt(PROMPT_SHELL);
		rl_on_new_line();
		printf("\n");
		rl_redisplay();
	}
	if (g_shell_status == running_cmd_line)
	{
		g_shell_status = reading_cmd_line;
		printf("\n");
	}
	return (0);
}

/*
*Signal getter, actually small but easy to improve
*/
void	get_sig(int sig)
{
	if (sig == SIGINT)
		get_sigint();
}
