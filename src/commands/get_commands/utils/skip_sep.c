/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_sep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:00:53 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/10 09:48:31 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_sep(const char *input, int input_size, int *i)
{
	const char	*sep_arg[] = {OR, AND, PIPE, REDIR_HEREDOC_STDIN, REDIR_STDIN,
		REDIR_APPEND_STDOUT, REDIR_STDOUT, REDIR_STDERR};
	int			i_sep;

	i_sep = 0;
	while (i_sep < 8)
	{
		if (is_sep_equal_to(sep_arg[i_sep], input, input_size, *i))
		{
			*i += ft_strlen(sep_arg[i_sep]);
			return ;
		}
		i_sep++;
	}
}
