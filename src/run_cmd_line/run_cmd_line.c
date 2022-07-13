/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 19:34:15 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/13 00:48:19 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_line.h"
#include "run_cmd_line.h"
#include "shell.h"
#include "tree.h"

extern int	g_shell_status;

int	run_cmd_line(t_tree *cmd_line, t_shell *shell)
{
	const t_run_cmd_node	run_cmd_node[] = {run_cmd_or, run_cmd_and,
		run_cmd_pipe, run_cmd_args};
	int						i_node;

	if (g_shell_status == reading_cmd_line)
		return (0);
	i_node = ((t_node *) cmd_line->content)->tag;
	shell->return_value = (run_cmd_node[i_node])(cmd_line, shell);
	return (shell->return_value);
}
