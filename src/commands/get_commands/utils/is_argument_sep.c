/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_argument_sep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 01:09:38 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/10 12:07:45 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	is_argument_sep(const char *input, int input_size, int start)
{
	const char	*sep_arg[] = {OR, AND, PIPE, REDIR_STDIN, REDIR_HEREDOC,
		REDIR_STDOUT, REDIR_APPEND_STDOUT, REDIR_STDERR};
	int			i;

	i = 0;
	while (i < 8)
	{
		if (is_sep_equal_to(sep_arg[i], input, input_size, start))
			return (1);
		i++;
	}
	return (0);
}
