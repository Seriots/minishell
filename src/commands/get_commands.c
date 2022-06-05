/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 19:10:33 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/05 20:12:38 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

static char	**get_commands_from_input(const char *input, t_shell *shell)
{
	char	**commands;

	(void) shell;
	commands = ft_split(input, '|');
	if (!commands)
		return (NULL);
	return (commands);
}

char	**get_commands(t_shell *shell)
{
	char	*input;
	char	**commands;

	input = readline(SHELL_PROMPT);
	if (!input)
		return (NULL);
	add_history(input);
	commands = get_commands_from_input(input, shell);
	free(input);
	return (commands);
}
