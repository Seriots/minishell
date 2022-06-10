/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_argument_equal_to.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 23:58:14 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/09 17:36:28 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	is_argument_equal_to(const char *arg, const char *input, int input_size,
	int start)
{
	int	arg_size;
	int	is_equal;

	if (is_argument_sep(input, input_size, start))
		return (is_sep_equal_to(arg, input, input_size, start));
	arg_size = ft_strlen(arg);
	is_equal = start + arg_size < input_size;
	is_equal &= ft_strncmp(input + start, arg, arg_size) == 0;
	is_equal &= ft_strchr(END_SEP, input[start + arg_size]) != NULL;
	return (is_equal);
}
