/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_argument_equal_to.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 23:58:14 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/07 14:09:48 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	is_argument_equal_to(const char *arg, const char *input, int input_size,
	int start)
{
	int	arg_size;
	int	is_equal;

	arg_size = ft_strlen(arg);
	is_equal = start + arg_size < input_size;
	is_equal &= ft_strncmp(input + start, arg, arg_size) == 0;
	is_equal &= ft_strchr(END_SEP, input[start + arg_size]) != NULL;
	return (is_equal);
}
