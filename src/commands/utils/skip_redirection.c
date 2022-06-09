/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:00:53 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/09 03:25:16 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_redirection(const char *input, int input_size, int *i)
{
	const char	*redir_arg[] = {REDIR_HEREDOC_STDIN, REDIR_STDIN,
		REDIR_APPEND_STDOUT, REDIR_STDOUT};
	int			i_redir;

	i_redir = 0;
	while (i_redir < REDIR_NBR)
	{
		if (is_redirection_equal_to(redir_arg[i_redir], input, input_size, *i))
		{
			*i += ft_strlen(redir_arg[i_redir]);
			return ;
		}
		i_redir++;
	}
}
