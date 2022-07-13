/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:40:53 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/13 10:22:27 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "shell.h"

/*
* echo builtin command, handle the option -n at first
* element of char **arguments.
* Printf on standard output, each elements separated by one space
*/

int	is_option(char *argument)
{
	size_t	i;

	if (argument[0] != '-')
		return (0);
	i = 1;
	while (argument[i])
	{
		if (argument[i] != 'n')
			return (0);
		i ++;
	}
	return (1);
}

int	set_nb_option(char **arguments)
{
	int		i;
	int		j;
	char	*argument;

	j = 0;
	while (arguments[j])
	{
		argument = arguments[j];
		if (argument[0] != '-')
			return (j);
		i = 1;
		while (argument[i])
		{
			if (argument[i] != 'n')
				return (j);
			i ++;
		}
		j ++;
	}
	return (j);
}

int	echo_command(t_shell *shell, char **arguments)
{
	size_t	option;
	size_t	i;

	(void)shell;
	if (!arguments)
		return (1);
	if (arguments[0] == 0)
		option = 0;
	else if (is_option(arguments[0]))
		option = set_nb_option(arguments);
	else
		option = 0;
	i = option;
	while (arguments[i])
	{
		if (i != option)
			ft_printf(" ");
		ft_printf("%s", arguments[i]);
		i ++;
	}
	if (!option)
		ft_printf("\n");
	return (0);
}
