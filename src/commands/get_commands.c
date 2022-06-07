/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 19:10:33 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/07 21:00:15 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

t_tree	*get_commands(t_shell *shell)
{
	char	*input;
	t_tree	*commands;

	(void)shell;
	input = readline(SHELL_PROMPT);
	if (!input)
		return (NULL);
	add_history(input);
	commands = parse_input(input, ft_strlen(input));
	free(input);
	return (commands);
}
