/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 08:06:26 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/10 08:33:37 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tree.h"

int	run_commands(t_tree *commands, t_shell *shell)
{
	int	return_value;

	if (set_heredocs(commands, shell) == -1)
		return (-1);
	return_value = run_tree_commands(commands, shell);
	free_commands(commands);
	return (return_value);
}
