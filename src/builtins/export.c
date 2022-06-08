/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:49:17 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/08 23:00:43 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/libft.h"
#include <stdlib.h>

int	export_command(t_shell *shell, char **arguments)
{
	size_t	i;
	t_dict	*new;

	i = 0;
	if (ft_arraylen(arguments) == 0)
	{
		/*new dico + algo de tri*/
		ft_dictprint(shell->env, "declare -x ");
		return (0);
	}	
	while (arguments[i])
	{
		new = getarg_env(arguments[i]);
		if (!new)
			return (-1);
		ft_dictadd_back(&shell->env, new, free, free);
		i++;
	}
}


int	main(int argc, char *argv[], char **env)
{
	t_shell	shell;

	init_shell(&shell, env);
	argv = &argv[1];
	export_command(&shell, argv);
	//ft_dictprint(shell.env, 0);
}
