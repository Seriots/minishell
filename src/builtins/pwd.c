/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:25:34 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/26 14:48:20 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"
#include "../../include/ft_printf.h"
#include "../../include/minishell.h"

/*
* pwd builtin command, IDK if a '\n' is needed.
*/
int	pwd_command(t_shell *shell, char **arguments)
{
	(void)arguments;
	if (!shell || !shell->directory)
		return (1);
	ft_printf("%s\n", shell->directory);
	return (0);
}
