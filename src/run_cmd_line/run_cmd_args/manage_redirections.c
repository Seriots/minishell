/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:32:11 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/05 23:12:59 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int	manage_redirections(t_tree *cmd_line)
{
	t_node	*content;
	int		ret_value;
	int		i;

	i = 0;
	ret_value = 0;
	content = (t_node *)cmd_line->content;
	while (content->redirs[i])
	{
		if (content->redirs[i]->tag == to_stdin)
			ret_value = manage_stdin(content->redirs[i]);
		else if (content->redirs[i]->tag == to_stdout)
			ret_value = manage_stdout(content->redirs[i]);
		else if (content->redirs[i]->tag == append_to_stdout)
			ret_value = manage_append_stdout(content->redirs[i]);
		else if (content->redirs[i]->tag == heredoc)
			ret_value = manage_heredoc(content->redirs[i]);
		else if (content->redirs[i]->tag == to_stderr)
			ret_value = manage_stderr(content->redirs[i]);
		if (ret_value)
			return (ret_value);
		i ++;
	}
	return (0);
}