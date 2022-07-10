/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 19:41:38 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/10 22:05:28 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <sys/types.h>
# include <signal.h>

//	handle_signals.c
void				get_sig_heredoc(int sig);
void				get_sig_child(int sig);
void				get_sig(int sig);

//	init_sigact.c
struct sigaction	init_sigact(void);
struct sigaction	init_sigact_child(void);
struct sigaction	init_sigact_ignore(void);

#endif
