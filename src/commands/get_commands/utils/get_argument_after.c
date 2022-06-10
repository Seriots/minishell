/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argument_after.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 00:33:56 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/07 14:26:59 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "minishell.h"

char	*get_argument_after(const char *arg, const char *input, int input_size)
{
	int	i;

	i = 0;
	skip_to(arg, input, input_size, &i);
	skip_to_next_argument(input, input_size, &i);
	if (i >= input_size)
		return (NULL);
	return (get_argument(input, input_size, i));
}
