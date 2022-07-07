/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 10:42:07 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/07 04:00:44 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_builtins(t_shell **shell)
{
	(*shell)->builtins[0] = &cd_command;
	(*shell)->builtins[1] = &echo_command;
	(*shell)->builtins[2] = &env_command;
	(*shell)->builtins[3] = &exit_command;
	(*shell)->builtins[4] = &export_command;
	(*shell)->builtins[5] = &pwd_command;
	(*shell)->builtins[6] = &unset_command;
}
