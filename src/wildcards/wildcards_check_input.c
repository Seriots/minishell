/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_check_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:29:14 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/20 15:31:36 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../include/libft.h"
#include "../../include/minishell.h"
#include "../../include/ft_printf.h"
#include "../../include/list.h"

int	check_first_part(char *input, char *name)
{
	unsigned int	i;

	i = 0;
	if (input[i] == '*')
		return (1);
	while (input[i] && name[i] && input[i] != '*')
	{
		if (input[i] != name[i])
			return (0);
		i ++;
	}
	if (input[i] == '*' && input[i - 1] == name[i - 1])
		return (1);
	if (input[i] == name[i])
		return (1);
	else
		return (0);
}

int	check_last_part(char *input, char *name, unsigned int last_pos)
{
	size_t	i;
	size_t	size_input;
	size_t	size_name;

	if (last_pos != 0)
		name[last_pos - 1] = 0;
	i = 0;
	name = &name[last_pos];
	size_input = ft_strlen(input);
	size_name = ft_strlen(name);
	if (input[size_input - i - 1] == '*')
		return (1);
	while (size_input - i && size_name - i && input[size_input - i - 1] != '*')
	{
		if (input[size_input - i - 1] != name[size_name - i - 1])
			return (0);
		i ++;
	}
	if (input[size_input - i - 1] == '*' && input[size_input - i]
		== name[size_name - i])
		return (1);
	if (input[size_input - i - 1] == name[size_name - i - 1])
		return (1);
	else
		return (0);
}

int	check_middle_part(char *input, char *name,
	unsigned int *position, int *next_str)
{
	char	*substr;

	substr = get_substr(input, *next_str);
	if (!substr)
		return (0);
	while (name[*position] && comp(&name[*position], substr, ft_strlen(substr)))
		*position += 1;
	if (name[*position])
	{
		*position += ft_strlen(substr);
		*next_str = get_next_str(input, *next_str);
	}
	free(substr);
	return (1);
}
