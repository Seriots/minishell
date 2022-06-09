/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_to_next_argument.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 00:25:31 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/07 00:26:51 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_to_next_argument(const char *input, int input_size, int *i)
{
	skip_argument(input, input_size, i);
	skip_whitespaces(input, input_size, i);
}
