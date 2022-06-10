/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 02:41:30 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/09 02:45:35 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "tree.h"

t_tree	*get_commands(t_shell *shell)
{
	char	*input;
	t_tree	*commands;

	(void) shell;
	input = readline(SHELL_PROMPT);
	if (!input)
		return (NULL);
	add_history(input);
	commands = parse_input(input, ft_strlen(input));
	free(input);
	return (commands);
}