/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 01:19:53 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/07 14:00:02 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_redirections(const char *input, int input_size, int *i)
{
	while (is_argument_redirection(input, input_size, *i))
	{
		skip_redirection(input, input_size, i);
		skip_to_next_argument(input, input_size, i);
	}
}
