/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 19:10:33 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/06 19:32:04 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

t_tree	*get_commands(t_shell *shell)
{
	char	*input;
	t_tree	*commands;

	input = readline(SHELL_PROMPT);
	if (!input)
		return (NULL);
	add_history(input);
	commands = parse_input(input, ft_strlen(input));
	free(input);
	return (commands);
}
