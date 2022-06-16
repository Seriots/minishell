/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:12:00 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/15 15:27:34 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include "../include/libft.h"
#include "../include/ft_printf.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>

#define PROMPT "Enter your command: "
/*
* get sigint (Ctrl + C)
*/
int	get_sigint(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	ft_printf("\n");
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

char	*rl_gets (void)
{
	char	*line_read;
	line_read = readline(PROMPT);
	if (line_read && *line_read)
		add_history (line_read);
	return (line_read);
}

struct sigaction	init_sigact(void)
{
	struct sigaction	sigact;

	ft_memset(&sigact, '\0', sizeof(sigact));
	sigact.sa_sigaction = get_sig;
	sigact.sa_flags = SA_SIGINFO;
	return (sigact);
}

int	main(void)
{

	int					end;
	char				*command;
	struct sigaction	sigact;

	sigact = init_sigact();
	end = 0;
	sigaction(SIGINT, &sigact, NULL);
	sigaction(SIGQUIT, &sigact, NULL);
	while (!end)
	{
		command = rl_gets();
		if (!command)
			end = 1;
		else
			ft_printf("command = %s\n", command);
		free(command);
	}
	rl_clear_history();
	return (0);
}