/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:21:41 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/11 23:28:08 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "builtins.h"
#include "dict.h"
#include "libft.h"
#include "shell.h"

static int	is_minus(t_shell **shell)
{
	char	*wit;
	t_dict	*pwd;
	t_dict	*oldpwd;
	int		error;

	pwd = dict_getelem_key((*shell)->env, "PWD");
	oldpwd = dict_getelem_key((*shell)->env, "OLDPWD");
	if (!pwd)
		return (ft_putstr_fd("minishell: cd: PWD not set\n", 2), 1);
	if (!oldpwd)
		return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2), 1);
	error = chdir(oldpwd->value);
	if (error)
		return (print_error_message_cd(oldpwd->value), 1);
	wit = pwd->value;
	pwd->value = oldpwd->value;
	oldpwd->value = wit;
	if (pwd->value)
		printf("%s\n", (char *)pwd->value);
	return (0);
}

static int	set_pwd_to_home(t_shell **shell)
{
	t_dict	*home;
	char	*home_path;
	int		error;

	home = dict_getelem_key((*shell)->env, "HOME");
	if (!home)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	home_path = home->value;
	if (!home_path)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	error = chdir(home_path);
	if (error)
		return (print_error_message_cd(home_path), 1);
	return (0);
}

static int	change_directory(char *path)
{
	int	error;

	error = chdir(path);
	if (error)
		print_error_message_cd(path);
	return (error);
}

int	cd_command(t_shell *shell, char **arguments)
{
	int	error;

	error = 0;
	if (ft_arraylen(arguments) > 1)
		return (ft_putstr_fd("minishell: cd: too many arguments\n",
				STDERR_FILENO), 1);
	else if (ft_arraylen(arguments) == 0)
		error = set_pwd_to_home(&shell);
	else if (!ft_strncmp(arguments[0], "-", ft_strlen(arguments[0])))
		error = is_minus(&shell);
	else if (!ft_strncmp(arguments[0], ".", ft_strlen(arguments[0])))
		error = 0;
	else
		error = change_directory(arguments[0]);
	if (error)
		return (1);
	free(shell->directory);
	shell->directory = get_current_directory();
	if (update_pwd(&shell, shell->directory))
		return (1);
	if (!shell->directory)
		return (1);
	return (0);
}
