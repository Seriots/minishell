/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_redirs_modification.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:31:00 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/13 23:34:23 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "read_cmd_line.h"
#include "run_cmd_line.h"
#include "shell.h"
#include "libft.h"
#include "wildcards.h"

static char	*input_modification_heredoc(char *heredoc, int is_quoted,
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

static void	redirs_modification_error(char *input)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(input, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
}

static char	**init_array_input(char *input)
{
	char	**array_input;

	array_input = malloc(sizeof(char *) * 2);
	if (!array_input)
		return (NULL);
	array_input[0] = ft_strdup(input);
	if (!array_input[0])
		return (free(array_input), NULL);
	array_input[1] = NULL;
	return (array_input);
}

static int	redirs_modification(char **input, t_shell *shell)
{
	char	**array_input;

	array_input = init_array_input(*input);
	if (!array_input)
		return (1);
	array_input = replace_special_args(array_input, shell);
	if (!array_input)
		return (free(array_input), 1);
	array_input = change_vars_in_args(array_input, shell->env);
	if (!array_input)
		return (free(array_input), 1);
	array_input = split_with_quote(array_input);
	if (!array_input)
		return (free(array_input), 1);
	array_input = replace_args(array_input);
	if (!array_input)
		return (free(array_input), 1);
	if (ft_arraylen(array_input) > 1)
		return (redirs_modification_error(*input), ft_free_tab(array_input), 2);
	free(*input);
	*input = array_input[0];
	free(array_input);
	return (0);
}

int	all_redirs_modification(t_redir ***redirs_addr, t_shell *shell)
{
	int		i;
	int		error;
	t_redir	**redirs;

	i = 0;
	redirs = *redirs_addr;
	while (redirs[i])
	{
		if (redirs[i]->tag == heredoc)
		{
			redirs[i]->heredoc = input_modification_heredoc(redirs[i]->heredoc,
					redirs[i]->is_quoted, shell);
			if (!redirs[i]->heredoc)
				return (1);
		}
		else
		{
			error = redirs_modification(&(redirs[i]->pathfile), shell);
			if (error)
				return (error);
		}
		i ++;
	}
	return (0);
}
