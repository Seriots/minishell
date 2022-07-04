/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_modification_checker.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 23:27:24 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/04 23:27:47 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/get_next_line.h"
#include "../../../include/libft.h"
#include "../../../include/dict.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int	main(int argc, char *argv[], char **env)
{
	t_shell	shell;
	char	**result;
	char	**input;
	int		i;
	int		fd;
	char	**args;
	char	*line;

	init_shell(&shell, env);
	fd = open("src/input_modification/checker/input_modification_test.txt",
			O_RDONLY);
	line = get_next_line(fd);
	if (line && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	args = ft_split(line, ' ');
	while (args)
	{
		i = -1;
		result = input_modification(args, &shell);
		while (result[++i] && result)
		{
			if (i != 0)
				printf(" ");
			printf("%s", result[i]);
		}
		printf("\n");
		ft_free_tab(result);
		line = get_next_line(fd);
		if (line && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		args = ft_split(line, ' ');
	}
	free_shell(&shell);
}
