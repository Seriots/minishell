/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:29:52 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/14 00:45:32 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "dict.h"
#include "libft.h"
#include "run_cmd_line.h"

int	make_check_char(char *input, t_dict *env, int *pos, char **result)
{
	static char		quote;
	static size_t	nb_letters;
	char			*var;

	if (input[*pos] == '\'' || input[*pos] == '\"')
	{
		quote = update_quote(quote, input[*pos]);
		(*result)[nb_letters++] = input[*pos];
	}
	else if (input[*pos] == '$'
		&& quote != '\'' && ft_is_varchar(input[*pos + 1]))
	{
		if (set_var(&var, input, *pos + 1) == -1)
			return (-1);
		nb_letters += concat_var(var, env, result, nb_letters);
		*pos += ft_strlen(var);
		free(var);
	}
	else
		(*result)[nb_letters++] = input[*pos];
	if (!input[*pos] || !input[*pos + 1])
		quote = 0;
	if (!input[*pos] || !input[*pos + 1])
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
			free (result);
			return (0);
		}
		if (input[pos])
			pos++;
	}
	free(input);
	return (result);
}

int	check_char(char *input, t_dict *env, int *pos, size_t *nb_letters)
{
	static char	quote;
	char		*var;

	var = 0;
	if (input[*pos] == '\'' || input[*pos] == '\"')
	{
		quote = update_quote(quote, input[*pos]);
		*nb_letters += 1;
	}
	else if (input[*pos] == '$'
		&& quote != '\'' && ft_is_varchar(input[*pos + 1]))
	{
		if (set_var(&var, &input[1], *pos) == -1)
			return (-1);
		*nb_letters += get_size_var(var, env);
		*pos += ft_strlen(var);
		free(var);
	}
	else
		*nb_letters += 1;
	if (!input[*pos] || !input[*pos + 1])
		quote = 0;
	return (0);
}

char	*get_env_arguments(char *input, t_dict *env)
{
	int		pos;
	int		is_error;
	size_t	nb_letters;

	pos = 0;
	nb_letters = 0;
	while (input[pos])
	{
		is_error = check_char(input, env, &pos, &nb_letters);
		if (is_error)
		{
			free (input);
			return (0);
		}
		if (input[pos])
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
