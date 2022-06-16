/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 22:42:20 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/15 15:29:01 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include "read_cmd_line.h"
#include "tree.h"
#include "../../include/libft.h"
#include "../../include/minishell.h"

static int	set_cmd_line(const char *input, t_tree **cmd_line)
{
	t_token	*tokens;
	int		ret_value_parse;

	if (lexer(input, &tokens) == -1)
		return (-1);
	ret_value_parse = parse(input, tokens, cmd_line);
	free(tokens);
	return (ret_value_parse);
}

int	read_cmd_line(t_tree **cmd_line)
{
	char	*input;
	int		ret_value_set_cmd_line;

	input = readline(SHELL_PROMPT);
	if (!input)
		return (-1);
	add_history(input);
	ret_value_set_cmd_line = set_cmd_line(input, cmd_line);
	free(input);
	return (ret_value_set_cmd_line);
}
