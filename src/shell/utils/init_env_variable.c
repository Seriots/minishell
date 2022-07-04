/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_variable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 22:50:05 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/04 23:37:27 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/dict.h"
#include "../../../include/libft.h"
#include "../../../include/ft_printf.h"
#include "../../../include/minishell.h"
#include <stdlib.h>

int	free_and_set_error(char *key, char *value, int *error)
{
	free(key);
	free(value);
	*error -= 1;
	return (0);
}

int	set_default_variable(t_shell **shell)
{
	t_dict	*search;
	int		error;
	t_dict	**env;
	t_dict	**export;

	env = &(*shell)->env;
	export = &(*shell)->export;
	error = 0;
	search = dict_getelem_key(*env, "PWD");
	if (!search)
		add_pwd(env, &error);
	search = dict_getelem_key(*env, "SHLVL");
	if (!search)
		add_shlvl(env, &error);
	else
		update_shlvl(&search, &error);
	search = dict_getelem_key(*env, "_");
	if (!search)
		add_envpath(env, &error);
	search = dict_getelem_key(*env, "OLDPWD");
	if (!search)
		add_oldpwd(export, &error);
	return (error);
}
