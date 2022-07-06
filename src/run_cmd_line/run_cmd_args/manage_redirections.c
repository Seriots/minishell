/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:32:11 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/06 16:56:08 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int	manage_redirections(t_tree *cmd_line)
{
	t_redir	**redirs;
	int		ret_value;
	int		i;

	i = 0;
	redirs = (t_redir **)((t_node *) cmd_line->content)->redirs;
	while (redirs[i])
	{
		ret_value = -1;
		if (redirs[i]->tag == to_stdout)
			ret_value = manage_stdout(redirs[i]);
		else if (redirs[i]->tag == to_stdin)
			ret_value = manage_stdin(redirs[i]);
		else if (redirs[i]->tag == append_to_stdout)
			ret_value = manage_append_stdout(redirs[i]);
		else if (redirs[i]->tag == heredoc)
			ret_value = manage_heredoc(redirs[i]);
		else if (redirs[i]->tag == to_stderr)
			ret_value = manage_stderr(redirs[i]);
		if (ret_value)
			return (ret_value);
		i++;
	}
	return (0);
}
