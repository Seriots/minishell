/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_special_args_heredoc.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:14:22 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/13 15:17:36 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "shell.h"
#include "run_cmd_line.h"

size_t	count_letters_plus_special_heredoc(char *input, t_shell *shell)
{
	size_t	size;
	size_t	i;

	size = 0;
	i = 0;
	while (input[i])
	{
		if (!ft_strncmp(&input[i], "$?", 2))
			size += count_q_mark(&i, ft_itoa(shell->return_value));
		else
		{
			i ++;
			size ++;
		}
	}
	return (size);
}

size_t	input_plus_special_char_heredoc(char **new, char *input, t_shell *shell)
{
	size_t	size;
	size_t	i;

	size = 0;
	i = 0;
	while (input[i])
	{
		if (!ft_strncmp(&input[i], "$?", 2))
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

char	*replace_special_char_heredoc(char *input, t_shell *shell)
{
	char	*new_str;
	size_t	size;

	size = count_letters_plus_special_heredoc(input, shell);
	(void)size;
	new_str = ft_calloc(sizeof(char), size + 1);
	if (!new_str)
	{
		free (input);
		return (0);
	}
	input_plus_special_char_heredoc(&new_str, input, shell);
	free(input);
	return (new_str);
}
