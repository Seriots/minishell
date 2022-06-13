/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_tree_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 08:11:58 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/13 15:40:26 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "list.h"
#include "minishell.h"
#include "tree.h"

static int	run_or_commands(t_tree *commands, t_shell *shell)
{
	int		return_value;
	t_list	*sub_commands;

	return_value = 1;
	sub_commands = commands->childs;
	while (return_value != -1 && sub_commands && return_value != 0)
	{
		return_value = run_tree_commands(sub_commands->content, shell);
		sub_commands = sub_commands->next;
	}
	return (return_value);
}

static int	run_and_commands(t_tree *commands, t_shell *shell)
{
	int		return_value;
	t_list	*sub_commands;

	return_value = 0;
	sub_commands = commands->childs;
	while (return_value != -1 && sub_commands && return_value == 0)
	{
		return_value = run_tree_commands(sub_commands->content, shell);
		sub_commands = sub_commands->next;
	}
	return (return_value);
}

int	run_tree_commands(t_tree *commands, t_shell *shell)
{
	if (!commands)
		return (-1);
	if (!commands->childs)
		return (run_command(commands->content, shell));
	if (ft_strcmp(OR, commands->content) == 0)
		return (run_or_commands(commands, shell));
	if (ft_strcmp(AND, commands->content) == 0)
		return (run_and_commands(commands, shell));
	if (ft_strcmp(PIPE, commands->content) == 0)
		return (run_pipe_commands(commands, shell));
	ft_putstr_fd("Error: Wrong format node identifier", 2);
	return (-1);
}
