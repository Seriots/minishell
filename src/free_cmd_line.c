/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 03:55:02 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/04 13:50:02 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/libft.h"
#include "../include/minishell.h"

static void	free_redirs(t_redir **redirs)
{
	int	i;

	i = 0;
	while (redirs[i])
	{
		if (redirs[i]->tag == heredoc && redirs[i]->heredoc)
			free(redirs[i]->heredoc);
		else if (redirs[i]->pathfile)
			free(redirs[i]->pathfile);
		free(redirs[i]);
		i++;
	}
	free(redirs);
}

void	free_cmd_line(void *node_addr)
{
	t_node	*node;

	node = (t_node *) node_addr;
	if (node->tag == args && node->args)
		ft_free_tab(node->args);
	if (node->tag == args && node->redirs)
		free_redirs(node->redirs);
	free(node);
}
