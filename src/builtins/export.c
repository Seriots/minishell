/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:49:17 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/09 16:05:09 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/dict.h"
#include "../../include/libft.h"
#include "../../include/minishell.h"
#include <stdlib.h>


int	export_command(t_shell *shell, char **arguments)
{
	size_t	i;
	t_dict	*new;
	t_dict	*copy;

	i = 0;
	if (ft_arraylen(arguments) == 0)
	{
		/*new dico + algo de tri*/
		copy = dict_copy(shell->env);
		dict_print(copy, "copy ");
		dict_print(shell->env, "envi ");
		dict_clear(copy, free, free);
		return (0);
	}	
	while (arguments[i])
	{
		new = getarg_env(arguments[i]);
		if (!new)
			return (-1);
		dict_add_back(&shell->env, new, free, free);
		i++;
	}
}


int	main(int argc, char *argv[], char **env)
{
	t_shell	shell;

	init_shell(&shell, env);
	argv = &argv[1];
	export_command(&shell, argv);
	//dict_print(shell.env, 0);
	dict_clear(shell.env, free, free);
	free(shell.directory);
}
