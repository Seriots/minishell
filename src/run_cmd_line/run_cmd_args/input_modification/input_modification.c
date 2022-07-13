/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_modification.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:53:26 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/13 15:32:29 by lgiband          ###   ########.fr       */
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
	input = replace_args(input);
	return (input);
}

char	*input_modification_heredoc(char *heredoc, int is_quoted,
	t_shell *shell)
{
	if (!heredoc)
		return (0);
	if (is_quoted)
		return (heredoc);
	heredoc = replace_special_char_heredoc(heredoc, shell);
	if (!heredoc)
		return (0);
	heredoc = get_env_arguments_heredoc(heredoc, shell->env);
	if (!heredoc)
		return (0);
	return (heredoc);
}
