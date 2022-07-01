/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_and.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 19:52:11 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/01 04:16:16 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "minishell.h"
#include "run_cmd_line.h"
#include "tree.h"

int	run_cmd_and(t_tree *cmd_line, t_shell *shell)
{
	t_list	*list_and;
	int		ret_value;

	list_and = cmd_line->childs;
	ret_value = 0;
	while (list_and && ret_value == 0)
	{
		ret_value = run_cmd_line(list_and->content, shell);
		list_and = list_and->next;
	}
	return (ret_value);
}
