/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sigact.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:31:08 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/06 14:38:34 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <signal.h>
#include "../../include/minishell.h"
#include "../../include/libft.h"

/*
*Initialisation of signal handler object
*/
struct sigaction	init_sigact(void)
{
	struct sigaction	sigact;

	ft_memset(&sigact, '\0', sizeof(sigact));
	sigact.sa_sigaction = get_sig;
	sigact.sa_flags = SA_SIGINFO;
	return (sigact);
}

struct sigaction	init_sigact_heredoc(void)
{
	struct sigaction	sigact;

	ft_memset(&sigact, '\0', sizeof(sigact));
	sigact.sa_sigaction = get_sig_heredoc;
	sigact.sa_flags = SA_SIGINFO;
	return (sigact);
}
