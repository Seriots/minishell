/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_or.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 19:47:50 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/13 02:05:05 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "run_cmd_line.h"
#include "shell.h"
#include "tree.h"

extern t_shell_status	g_shell_status;

int	run_cmd_or(t_tree *cmd_line, t_shell *shell)
{
	t_list	*list_or;
	int		ret_value;

	list_or = cmd_line->childs;
	ret_value = -1;
	while ((g_shell_status == running_cmd_line
			|| g_shell_status == running_subshell_cmd_line)
		&& list_or && ret_value != 0)
	{
		ret_value = run_cmd_line(list_or->content, shell);
		list_or = list_or->next;
	}
	return (ret_value);
}
