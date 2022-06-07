/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:40:53 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/07 14:19:16 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "../../include/minishell.h"

/*
* echo builtin command, handle the option -n at first element of char **arguments.
* Printf on standard output, each elements separated by one space
*/
int	echo_command(char **arguments)
{
	size_t	option;
	size_t	i;

	if (!arguments)
		return (-1);
	if (arguments[0] == 0)
		option = 0;
	else if (!ft_strncmp("-n", arguments[0], ft_strlen(arguments[0])))
		option = 1;
	else
		option = 0;
	i = option;
	while (arguments[i])
	{
		if (i != option)
			write(1, " ", 1);
		write(1, arguments[i], ft_strlen(arguments[i]));
		i ++;
	}
	if (!option)
		write(1, "\n", 1);
	return (0);
}

/*
int main(int argc, char *argv[])
{
	argv = &argv[1];
	echo_command(argv);
}
*/