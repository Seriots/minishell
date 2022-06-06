/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_whitespaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 00:00:59 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/07 00:01:27 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	skip_whitespaces(const char *input, int input_size, int *i)
{
	while (*i < input_size && ft_strchr(WHITESPACES, input[*i]) != NULL)
		*i += 1;
}
