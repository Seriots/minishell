/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 20:03:47 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/06 19:50:20 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <signal.h>

# define SHELL_PROMPT "$> "

typedef struct s_shell
{
	char	**env;
}	t_shell;

void				free_commands(char **commands);
char				**get_commands(t_shell *shell);
int					run_commands(char **commands, t_shell *shell);

/*
//	SHELL
*/
int					free_shell(t_shell *shell);
int					init_shell(t_shell *shell, char **env);
int					run_shell(t_shell *shell);

/*
// SIGNALS
*/

/*handle_signals.c*/
void				get_sig(int sig, siginfo_t *siginfo, void *context);

/*init_sigact.c*/
struct sigaction	init_sigact(void);
#endif
