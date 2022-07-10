/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sigact.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:31:08 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/10 21:56:04 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft.h"
#include "signals.h"

/*
*Initialisation of signal handler object
*/
struct sigaction	init_sigact(void)
{
	struct sigaction	sigact;

	ft_memset(&sigact, '\0', sizeof(sigact));
	sigact.sa_handler = &get_sig;
	sigact.sa_flags = SA_SIGINFO;
	return (sigact);
}

struct sigaction	init_sigact_ignore(void)
{
	struct sigaction	sigact;

	ft_memset(&sigact, '\0', sizeof(sigact));
	sigact.sa_handler = SIG_IGN;
	sigact.sa_flags = SA_SIGINFO;
	return (sigact);
}

struct sigaction	init_sigact_child(void)
{
	struct sigaction	sigact;

	ft_memset(&sigact, '\0', sizeof(sigact));
	sigact.sa_handler = SIG_DFL;
	sigact.sa_flags = SA_SIGINFO;
	return (sigact);
}
