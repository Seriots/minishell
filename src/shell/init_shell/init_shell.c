/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 22:56:16 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/12 16:59:49 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "shell.h"

extern t_shell_status	g_shell_status;

char	*get_space(char *str, size_t *length)
{
	char	*new_str;
	size_t	i;

	if (*length == 0)
		*length = 4096;
	else
		*length *= 2;
	new_str = ft_calloc(sizeof(char), *length + 1);
	if (!new_str)
		return (0);
	if (!str)
		return (new_str);
	i = -1;
	while (str[++i])
		new_str[i] = str[i];
	free(str);
	return (new_str);
}

char	*get_current_directory(void)
{
	char	*path;
	char	*try;
	size_t	length;

	length = 0;
	try = 0;
	path = 0;
	while (!try)
	{
		path = get_space(path, &length);
		if (!path)
			return (0);
		try = getcwd(path, length);
	}
	length = ft_strlen(path);
	try = ft_calloc(sizeof(char), length + 1);
	if (!try)
		return (0);
	ft_strlcpy(try, path, length + 1);
	free(path);
	return (try);
}

t_dict	*getarg_env(char *line)
{
	t_dict	*elem;
	size_t	value_count;
	size_t	key_count;
	char	*value;
	char	*key;

	value_count = 0;
	key_count = 0;
	while (line[key_count] != '=' && line[key_count])
		key_count ++;
	if (!line[key_count])
		return (0);
	while (line[key_count + value_count + 1])
		value_count ++;
	key = ft_substr(line, 0, key_count);
	if (!key)
		return (0);
	value = ft_substr(line, key_count + 1, value_count);
	if (!value)
		return (free(key), (void *)0);
	elem = dict_new(key, value);
	if (!elem)
		return (free(key), free(value), (void *)0);
	return (elem);
}

t_dict	*get_env(char **env)
{
	t_dict	*dict;
	t_dict	*new;
	size_t	i;

	if (!env)
		return (0);
	i = 0;
	dict = 0;
	while (env[i])
	{
		new = getarg_env(env[i]);
		if (new)
			dict_add_back(&dict, new, free, free);
		i ++;
	}
	return (dict);
}

int	init_shell(t_shell *shell, char **env)
{
	shell->return_value = 0;
	shell->export = 0;
	shell->directory = 0;
	shell->env_str = 0;
	shell->env = get_env(env);
	if (env && !shell->env)
		return (-1);
	shell->directory = get_current_directory();
	if (shell->directory == 0)
		return (-1);
	if (set_default_variable(&shell) == -1)
		return (-1);
	shell->env_str = dict_to_array(shell->env);
	if (!shell->env_str)
		return (-1);
	init_builtins(&shell);
	init_signals();
	return (0);
}
