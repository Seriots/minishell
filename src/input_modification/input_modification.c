/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_modification.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:53:26 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/06 22:53:54 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/libft.h"
#include <stdio.h>
#include <stdlib.h>

char	**input_modification(char **input, t_shell *shell)
{
	if (!input)
		return (0);
	input = replace_special_args(input, shell);
	if (!input)
		return (0);
	input = change_vars_in_args(input, shell->env);
	if (!input)
		return (0);
	input = replace_args(input);
	return (input);
}

/*
int	main(int argc, char *argv[])
{
	t_dict	*dict;
	char	**result;
	char	**input;
	int		i;

	dict = 0;
	i = -1;
	argv = &argv[1];
	input = ft_calloc(sizeof(char *), ft_arraylen(argv) + 1);
	if (!input)
		return (0);
	while (argv[++i])
	{
		input[i] = ft_calloc(sizeof(char), ft_strlen(argv[i]) + 1);
		ft_strlcpy(input[i], argv[i], ft_strlen(argv[i]) + 1);
	}
	dict_add_back(&dict, dict_new("oui", "nooir"), free, free);
	dict_add_back(&dict, dict_new("ok", "ko"), free, free);
	dict_add_back(&dict, dict_new("toi", "rip"), free, free);
	i = -1;
	result = input_modification(input, dict);
	if (!result)
	{
		dict_clear(dict, 0, 0);
		return (0);
	}
	while (result[++i])
	{
		printf("%s\n", result[i]);
		free (result[i]);
	}
	dict_clear(dict, 0, 0);
	free(result);
}*/
