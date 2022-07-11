/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 22:18:25 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/11 22:48:58 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	exit_command(t_shell *shell, char **arguments)
{
	(void) shell;
	if (!arguments || !arguments[0])
		return (-2);
	return (-2);
}
