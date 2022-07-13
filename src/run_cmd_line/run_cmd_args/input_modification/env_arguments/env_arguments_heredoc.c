/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_arguments_heredoc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:19:32 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/13 22:49:03 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "dict.h"
#include "libft.h"
#include "run_cmd_line.h"

int	make_check_char_heredoc(char *input, t_dict *env, int *pos, char **result)
{
	static size_t	nb_letters;
	char			*var;

	if (input[*pos] == '$' && ft_is_varchar(input[*pos + 1]))
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

int	check_char_heredoc(char *input, t_dict *env, int *pos, size_t *nb_letters)
{
	char		*var;

	var = 0;
	if (input[*pos] == '$' && ft_is_varchar(input[*pos + 1]))
	{
		var = get_var(&input[1], *pos);
		if (!var)
			return (-1);
		*nb_letters += get_size_var(var, env);
		*pos += ft_strlen(var);
		free(var);
	}
	else
		*nb_letters += 1;
	return (0);
}

char	*make_new_str_heredoc(char *input, t_dict *env, size_t nb_letters)
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
		is_error = make_check_char_heredoc(input, env, &pos, &result);
		if (is_error)
		{
			free (input);
			free (result);
			return (0);
		}
		pos += 1;
	}
	free(input);
	return (result);
}

char	*get_env_arguments_heredoc(char *input, t_dict *env)
{
	int		pos;
	int		is_error;
	size_t	nb_letters;

	pos = 0;
	nb_letters = 0;
	while (input[pos])
	{
		is_error = check_char_heredoc(input, env, &pos, &nb_letters);
		if (is_error)
		{
			free (input);
			return (0);
		}
		pos ++;
	}
	return (make_new_str_heredoc(input, env, nb_letters));
}
