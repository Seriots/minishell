/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_modification.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:53:26 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/13 23:31:40 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run_cmd_line.h"
#include "shell.h"
#include "wildcards.h"

char	**input_modification(char **input, t_shell *shell)
{
	if (!input)
		return (0);
	input = replace_special_args(input, shell);
	if (!input)
		return (0);
	input = change_vars_in_args(input, shell->env);
	if (!input)
		return (0);
	input = split_with_quote(input);
	if (!input)
		return (0);
	input = replace_args(input);
	return (input);
}
