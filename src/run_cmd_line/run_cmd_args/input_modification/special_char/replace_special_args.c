/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_special_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 00:20:24 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/13 15:14:33 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "shell.h"
#include "run_cmd_line.h"

size_t	count_letters_plus_special(char *input, t_shell *shell)
{
	size_t	size;
	size_t	i;
	size_t	quote;

	size = 0;
	i = 0;
	quote = 1;
	while (input[i])
	{
		if (input[i] == '\'')
			quote *= -1;
		if (!ft_strncmp(&input[i], "$?", 2) && quote == 1)
			size += count_q_mark(&i, ft_itoa(shell->return_value));
		else
		{
			i ++;
			size ++;
		}
	}
	return (size);
}

size_t	input_plus_special_char(char **new, char *input, t_shell *shell)
{
	size_t	size;
	size_t	i;
	size_t	quote;

	size = 0;
	i = 0;
	quote = 1;
	while (input[i])
	{
		if (input[i] == '\'')
			quote *= -1;
		if (!ft_strncmp(&input[i], "$?", 2) && quote == 1)
			size += replace_q_mark(&i, new, size, ft_itoa(shell->return_value));
		else
		{
			(*new)[size] = input[i];
			i ++;
			size ++;
		}
	}
	return (size);
}

char	*replace_special_char(char *input, t_shell *shell)
{
	char	*new_str;
	size_t	size;

	size = count_letters_plus_special(input, shell);
	(void)size;
	new_str = ft_calloc(sizeof(char), size + 1);
	if (!new_str)
	{
		free (input);
		return (0);
	}
	input_plus_special_char(&new_str, input, shell);
	free(input);
	return (new_str);
}

char	**replace_special_args(char **input, t_shell *shell)
{
	int	i;

	if (!input)
		return (0);
	i = 0;
	while (input[i])
	{
		input[i] = replace_special_char(input[i], shell);
		if (!input[i])
		{
			while (input[++i])
				free (input[i]);
			ft_free_tab(input);
			return (0);
		}
		i++;
	}
	return (input);
}
