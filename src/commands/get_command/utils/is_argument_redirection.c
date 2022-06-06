/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_argument_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 01:09:38 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/07 01:53:38 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_argument_redirection(const char *input, int input_size, int start)
{
	const char	*redir_arg = {REDIR_STDIN, REDIR_HEREDOC_STDIN, REDIR_STDOUT,
		REDIR_APPEND_STDOUT};
	int			i;

	i = 0;
	while (i < 4)
	{
		if (is_argument_equal_to(redir_arg[i], input, input_size, start))
			return (1);
		i++;
	}
	return (0);
}
