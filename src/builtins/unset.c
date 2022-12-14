/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:29:26 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/09 22:01:30 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "dict.h"
#include "libft.h"
#include "shell.h"

static int	invalid_identifier_unset(char *arg)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

static int	check_arg(char *arg)
{
	size_t	i;

	i = 0;
	if (!arg)
		return (0);
	if (ft_strlen(arg) == 1 && arg[0] == '_')
		return (2);
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && !(arg[i] == '_'))
			return (0);
		i++;
	}
	if (i == 0)
		return (0);
	return (1);
}

int	unset_command(t_shell *shell, char **arguments)
{
	size_t	i;
	int		error;
	int		return_error;

	i = 0;
	return_error = 0;
	if (!arguments || !arguments[0])
		return (0);
	while (arguments[i])
	{
		error = check_arg(arguments[i]);
		if (error == 1)
		{
			dict_delone(&shell->env,
				dict_getelem_key(shell->env, arguments[i]), free, free);
			dict_delone(&shell->export,
				dict_getelem_key(shell->export, arguments[i]), free, free);
		}
		else if (!error)
			return_error = invalid_identifier_unset(arguments[i]);
		i++;
	}
	return (return_error);
}
