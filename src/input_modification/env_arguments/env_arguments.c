/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:29:52 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/24 17:58:21 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../../include/minishell.h"
#include "../../../include/libft.h"
#include "../../../include/dict.h"
#include "../../../include/ft_printf.h"

int	make_check_char(char *input, t_dict *env, int *pos, char **result)
{
	static int		is_quoted;
	static size_t	nb_letters;
	char			*var;

	if (input[*pos] == '\'')
	{
		is_quoted = oppose_quote(is_quoted);
		(*result)[nb_letters] = input[*pos];
		nb_letters ++;
	}
	else if (input[*pos] == '$'
		&& is_quoted == 0 && ft_is_varchar(input[*pos + 1]))
	{
		var = get_var(input, *pos + 1);
		if (!var)
			return (-1);
		nb_letters += concat_var(var, env, result, nb_letters);
		*pos += ft_strlen(var);
		free(var);
	}
	else
		(*result)[nb_letters++] = input[*pos];
	if (input[*pos + 1] == '\0')
		nb_letters = 0;
	return (0);
}

char	*make_new_str(char *input, t_dict *env, size_t nb_letters)
{
	int		pos;
	int		is_error;
	char	*result;

	pos = 0;
	result = ft_calloc(sizeof(char), nb_letters + 1);
	if (!result)
	{
		free (input);
		return (0);
	}
	while (input[pos])
	{
		is_error = make_check_char(input, env, &pos, &result);
		if (is_error)
		{
			free (input);
			return (0);
		}
		pos += 1;
	}
	free(input);
	return (result);
}

int	check_char(char *input, t_dict *env, int *pos, size_t *nb_letters)
{
	static int	is_quoted;
	char		*var;

	var = 0;
	if (input[*pos] == '\'')
	{
		is_quoted = oppose_quote(is_quoted);
		*nb_letters += 1;
	}
	else if (input[*pos] == '$'
		&& is_quoted == 0 && ft_is_varchar(input[*pos + 1]))
	{
		var = get_var(&input[1], *pos);
		if (!var)
			return (-1);
		*nb_letters += get_size_var(var, env);
		pos += ft_strlen(var);
		free(var);
	}
	else
		*nb_letters += 1;
	return (0);
}

char	*get_env_arguments(char *input, t_dict *env)
{
	int		pos;
	int		is_error;
	size_t	nb_letters;

	pos = 0;
	nb_letters = 0;
	is_error = 0;
	while (input[pos])
	{
		is_error = check_char(input, env, &pos, &nb_letters);
		if (is_error)
		{
			free (input);
			return (0);
		}
		pos ++;
	}
	return (make_new_str(input, env, nb_letters));
}

/*
* Convert each array like '$...' to the corresponding value in the env.
* If the value isn't in the dict, '\0' the array is replace by '\0'.
*/
char	**change_vars_in_args(char **args, t_dict *env)
{
	int	i;

	i = 0;
	if (!args || !env)
		return (0);
	while (args[i])
	{
		args[i] = get_env_arguments(args[i], env);
		if (args[i] == 0)
		{
			while (args[++i])
				free(args[i]);
			ft_free_tab(args);
			return (0);
		}
		i ++;
	}
	return (args);
}

/*
int	main(int argc, char *argv[])
{
	t_dict	*dict;
	char	**result;
	int		i;

	dict = 0;
	i = -1;
	dict_add_back(&dict, dict_new("oui", "nooir"), free, free);
	dict_add_back(&dict, dict_new("ok", "ko"), free, free);
	dict_add_back(&dict, dict_new("toi", "rip"), free, free);
	result = change_vars_in_args(argv, dict);
	while (result[++i])
	{
		ft_printf("%s\n", result[i]);
		free (result[i]);
	}
	dict_clear(dict, 0, 0);
	free(result);
}*/
