/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:29:52 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/22 18:21:37 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../../include/minishell.h"
#include "../../include/libft.h"
#include "../../include/dict.h"
#include "../../include/ft_printf.h"

int	oppose_quote(int is_quoted)
{
	if (is_quoted)
		return (0);
	return (1);
}

char	*get_var(char *input, int pos)
{
	char	*var;
	size_t	size;
	
	size = 0;
	while (input[pos + size] != '\0' && input[pos + size] != ' ' && input[pos + size] != '$')
		size += 1;
	var = ft_calloc(sizeof(char), size + 1);
	if (!var)
		return (0);
	ft_strlcpy(var, &input[pos], size + 1);
	return (var);
}

size_t	get_size_var(char *var, t_dict *env)
{
	t_dict	*search;

	search = dict_getelem_key(env, var);
	if (!search)
		return (0);
	return (ft_strlen(search->value));
}

size_t	concat_var(char *var, t_dict *env, char **result, size_t nb_letters)
{
	t_dict	*search;

	search = dict_getelem_key(env, var);
	if (!search)
		return (0);
	ft_strlcat(*result, search->value, nb_letters + ft_strlen(search->value) + 1);
	return (ft_strlen(search->value));
}

int	ft_is_varchar(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*make_new_str(char *input, t_dict *env, size_t nb_letters)
{
	int		pos;
	int		is_quoted;
	char	*var;
	char	*result;

	pos = 0;
	var = 0;
	is_quoted = 0;
	result = ft_calloc(sizeof(char), nb_letters + 1);
	if (!result)
		return (0);
	nb_letters = 0;
	while (input[pos])
	{
		if (input[pos] == '\'')
		{
			is_quoted = oppose_quote(is_quoted);
			result[nb_letters] = input[pos];
			nb_letters ++;
		}
		else if (input[pos] == '$' && is_quoted == 0 && ft_is_varchar(input[pos + 1]))
		{
			var = get_var(&input[1], pos);
			if (!var)
				return (0);
			nb_letters += concat_var(var, env, &result, nb_letters);
			pos += ft_strlen(var);
			free(var);
		}
		else
		{
			result[nb_letters] = input[pos];
			nb_letters ++;
		}
		pos ++;
	}
	return (result);
}

char	*get_env_arguments(char *input, t_dict *env)
{
	int		pos;
	int		is_quoted;
	size_t	nb_letters;
	char	*var;

	pos = 0;
	var = 0;
	nb_letters = 0;
	is_quoted = 0;
	while (input[pos])
	{
		if (input[pos] == '\'')
		{
			is_quoted = oppose_quote(is_quoted);
			nb_letters ++;
		}
		else if (input[pos] == '$' && is_quoted == 0 && ft_is_varchar(input[pos + 1]))
		{
			var = get_var(&input[1], pos);
			if (!var)
				return (0);
			nb_letters += get_size_var(var, env);
			pos += ft_strlen(var);
			free(var);
		}
		else
			nb_letters ++;
		pos ++;
	}
	printf("%lu\n", nb_letters);
	return (make_new_str(input, env, nb_letters));
}

/*
int	main(int argc, char *argv[])
{
	t_dict	*dict;
	char	*result;

	dict = 0;
	dict_add_back(&dict,dict_new("oui", "nooir"), free, free);
	dict_add_back(&dict,dict_new("ok", "ko"), free, free);
	dict_add_back(&dict,dict_new("toi", "rip"), free, free);
	result = get_env_arguments(argv[1], dict);
	ft_printf("%s\n", result);
}*/