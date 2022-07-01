/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 19:34:15 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/01 02:29:31 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "run_cmd_line.h"
#include "tree.h"

int	run_cmd_line(t_tree *cmd_line, t_shell *shell)
{
	const t_run_cmd_node	run_cmd_node[] = {run_cmd_or, run_cmd_and,
		run_cmd_pipe, run_cmd_args};
	int						i_node;

	i_node = ((t_node *) cmd_line->content)->tag;
	return ((run_cmd_node[i_node])(cmd_line, shell));
}
