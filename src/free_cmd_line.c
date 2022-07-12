/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 03:55:02 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/12 20:55:25 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "cmd_line.h"

void	free_redir(t_redir *redir)
{
	if (redir->tag == heredoc && redir->heredoc)
		free(redir->heredoc);
	else if (redir->pathfile)
		free(redir->pathfile);
	free(redir);
}

static void	free_redirs(t_redir **redirs)
{
	int	i;

	i = 0;
	while (redirs[i])
	{
		free_redir(redirs[i]);
		i++;
	}
	free(redirs);
}

void	free_cmd_line_struct(void *node_addr)
{
	t_node	*node;

	if (!node_addr)
		return ;
	node = (t_node *) node_addr;
	if (node->tag == args && node->args)
		free(node->args);
	if (node->tag == args && node->redirs)
		free(node->redirs);
	free(node);
}

void	free_cmd_line(void *node_addr)
{
	t_node	*node;

	if (!node_addr)
		return ;
	node = (t_node *) node_addr;
	if (node->tag == args && node->args)
		ft_free_tab(node->args);
	if (node->tag == args && node->redirs)
		free_redirs(node->redirs);
	free(node);
}
