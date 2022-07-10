/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 13:31:01 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/10 13:35:40 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stddef.h>
#include "signals.h"

void	init_signals(void)
{
	struct sigaction	sigact;

	sigact = init_sigact();
	sigaction(SIGINT, &sigact, NULL);
	sigact = init_sigact_ignore();
	sigaction(SIGQUIT, &sigact, NULL);
}
