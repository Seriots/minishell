/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 20:19:59 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/20 22:07:35 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "checker.h"
#include "lexer.h"
#include "libft.h"
#include "read_cmd_line.h"

size_t	check_checker(int ret_value, FILE *stream)
{
	char	*line;
	size_t	n;

	line = NULL;
	if (getline(&line, &n, stream) <= 0)
		return (0);
	if ((ret_value == 0
		&& (ft_strcmp(line, "OK") == 0 || ft_strcmp(line, "OK\n") == 0))
		|| (ret_value == -1
		&& (ft_strcmp(line, "KO") == 0 || ft_strcmp(line, "KO\n") == 0)))
	{
		printf("\033[32m");
		printf("OK: ");
		printf("\033[0m");
	}
	else
	{
		printf("\033[31m");
		printf("KO: ");
		printf("\033[0m");
	}
	free(line);
	return (1);
}

int	main(void)
{
	FILE	*stream;
	char	*line;
	t_token	*tokens;
	int		ret_value;
	size_t	n;

	stream = fopen("ressources_test_checker.txt", "r");
	if (!stream)
		return (1);
	line = NULL;
	while (getline(&line, &n, stream) > 0)
	{
		if (lexer(line, &tokens) == -1)
		{
			free(line);
			return (1);
		}
		ret_value = checker(tokens, "");
		n = check_checker(ret_value, stream);
		free(tokens);
		printf("%s", line);
		free(line);
		line = NULL;
		if (!n)
			break ;
	}
	free(line);
	fclose(stream);
	return (0);
}
