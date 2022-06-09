/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:25:34 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/08 22:02:01 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"
#include "../../include/minishell.h"

/*
* pwd builtin command, IDK if a '\n' is needed.
*/
void	pwd_command(t_shell *shell, char **arguments)
{
	(void)arguments;
	/*if (!arguments)
		return ;
	if (arguments[0] == 0)*/
	ft_printf("%s", shell->directory);
	/*else
		write (1, "pwd: too many arguments", 24);
	write (1, "\n", 1);*/
}
