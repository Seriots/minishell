/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_part.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:00:17 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/22 13:00:44 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include "../../include/libft.h"
#include "../../include/ft_printf.h"
#include "../../include/list.h"
#include "../../include/minishell.h"

int	check_first_part(char *str, char *split, size_t *pos, size_t *pos_array)
{
	if (ft_strncmp(str, split, ft_strlen(split)) != 0)
		return (1);
	*pos += ft_strlen(split);
	*pos_array += 1;
	return (0);
}

int	check_middle_part(char *str, t_wildstr *split,
	size_t *pos, size_t *pos_array)
{
	while (str[*pos] && split->split[*pos_array]
		&& ((split->check_last && *pos_array != ft_arraylen(split->split) - 1)
			|| !split->check_last && *pos_array != ft_arraylen(split->split)))
	{
		if (ft_strncmp(&str[*pos], split->split[*pos_array],
				ft_strlen(split->split[*pos_array])) == 0)
		{	
			*pos += ft_strlen(split->split[*pos_array]) - 1;
			*pos_array += 1;
		}
		*pos += 1;
	}
	if (str[*pos] == 0
		&& ((split->check_last && *pos_array != ft_arraylen(split->split) - 1)
			|| *pos_array != ft_arraylen(split->split)))
		return (1);
	return (0);
}

int	check_last_part(char *str, char *split, size_t *pos, size_t *pos_array)
{
	while (str[*pos])
	{
		if (ft_strncmp(&str[*pos], split, ft_strlen(split) + 1) == 0)
		{
			*pos_array += 1;
			return (0);
		}
		*pos += 1;
	}
	return (1);
}
