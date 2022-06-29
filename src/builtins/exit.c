/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 22:18:25 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/29 13:53:30 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/dict.h"
#include "../../include/libft.h"
#include "../../include/ft_printf.h"
#include "../../include/minishell.h"
#include <stdlib.h>

int	exit_command(t_shell *shell, char **arguments)
{
	if (arguments)
		ft_free_tab(arguments);
	free_shell (shell);
	ft_printf("exit\n");
	exit (0);
	return (0);
}
