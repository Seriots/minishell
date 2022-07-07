/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:40:53 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/07 02:59:04 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "minishell.h"

/*
* echo builtin command, handle the option -n at first
* element of char **arguments.
* Printf on standard output, each elements separated by one space
*/
int	echo_command(t_shell *shell, char **arguments)
{
	size_t	option;
	size_t	i;

	(void)shell;
	if (!arguments)
		return (1);
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
			ft_printf(" ");
		ft_printf("%s", arguments[i]);
		i ++;
	}
	if (!option)
		ft_printf("\n");
	return (0);
}
