/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sep_equal_to.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 23:58:14 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/10 18:06:54 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	is_sep_equal_to(const char *sep, const char *input,	int input_size,
	int start)
{
	int	sep_size;
	int	is_equal;

	sep_size = ft_strlen(sep);
	if (start + sep_size >= input_size)
		return (0);
	is_equal = ft_strncmp(input + start, sep, sep_size) == 0;
	is_equal &= ft_strchr(END_SEP_NOT_WSPACE, input[start + sep_size]) == NULL;
	return (is_equal);
}
