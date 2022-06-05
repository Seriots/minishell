/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:59:42 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/05 19:31:43 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	run_shell(t_shell *shell)
{
	char	**commands;

	while (1)
	{
		commands = get_commands(shell);
		run_commands(commands, shell);
	}
	return (0);
}
