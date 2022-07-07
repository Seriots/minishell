/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:25:34 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/07 03:03:26 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

/*
* pwd builtin command, IDK if a '\n' is needed.
*/
int	pwd_command(t_shell *shell, char **arguments)
{
	(void)arguments;
	if (!shell || !shell->directory)
		return (1);
	printf("%s\n", shell->directory);
	return (0);
}
