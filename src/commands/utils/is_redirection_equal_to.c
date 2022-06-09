/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirection_equal_to.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 23:58:14 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/09 02:57:53 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	is_redirection_equal_to(const char *redir, const char *input, int input_size,
	int start)
{
	int	redir_size;
	int	is_equal;

	redir_size = ft_strlen(redir);
	is_equal = start + redir_size < input_size;
	is_equal &= ft_strncmp(input + start, redir, redir_size) == 0;
	is_equal &= ft_strchr(END_SEP_REDIR, input[start + redir_size]) == NULL;
	return (is_equal);
}
