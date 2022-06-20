/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 20:19:59 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/20 00:31:09 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lexer.h"
#include "libft.h"
#include "read_cmd_line.h"

int	check_crash(int ret_value)
{
	if (ret_value == -1)
	{
		printf("\033[32m");
		printf("OK Crash: ");
		printf("\033[0m");
	}
	else
	{
		printf("\033[31m");
		printf("KO No crash: ");
		printf("\033[0m");
	}
	return (1);
}

int	check_tokens(t_token *tokens, char **tokens_verif)
{
	const char	*token_str[] = {"NEWLINE", "PAR_LEFT", "PAR_RIGHT", "OR", "AND",
		"PIPE", "RED_HEREDOC", "RED_STDIN", "RED_APPEND_STDOUT", "RED_STDOUT",
		"RED_STDERR", "ARG"};
	int			i;

	i = 0;
	while (tokens_verif[i])
	{
		if (ft_strcmp(token_str[tokens[i].lexeme], tokens_verif[i]) != 0)
		{
			printf("\033[31m");
			printf("KO Token ");
			printf("%s", tokens_verif[i]);
			printf(": ");
			printf("\033[0m");
			return (1);
		}
		i++;
	}
	printf("\033[32m");
	printf("OK: ");
	printf("\033[0m");
	return (1);
}

void	remove_newline(char **tokens_verif)
{
	int	i;
	int	j;

	i = 0;
	while (tokens_verif[i])
		i++;
	if (i == 0)
		return ;
	i--;
	j = 0;
	while (tokens_verif[i][j])
		j++;
	if (j == 0)
		return ;
	j--;
	tokens_verif[i][j] = 0;
}

int	check(int ret_value, t_token *tokens, FILE *stream)
{
	char	*line;
	char	**tokens_verif;
	size_t	n;

	line = NULL;
	if (getline(&line, &n, stream) <= 0)
	{
		printf("\033[31m");
		printf("Result missing\n");
		printf("\033[0m");
		return (0);
	}
	if (ft_strcmp(line, "CRASH") == 0 || ft_strcmp(line, "CRASH\n") == 0)
	{
		free(line);
		return (check_crash(ret_value));
	}
	tokens_verif = ft_split(line, ' ');
	free(line);
	if (!tokens_verif)
		return (0);
	remove_newline(tokens_verif);
	check_tokens(tokens, tokens_verif);
	ft_free_tab(tokens_verif);
	return (1);
}

int	main(void)
{
	FILE	*stream;
	char	*line;
	t_token	*tokens;
	int		ret_value;
	size_t	n;

	stream = fopen("ressources_test_lexer.txt", "r");
	if (!stream)
		return (1);
	line = NULL;
	while (getline(&line, &n, stream) > 0)
	{
		ret_value = lexer(line, &tokens);
		n = check(ret_value, tokens, stream);
		if (ret_value != -1)
			free(tokens);
		printf("%s", line);
		free(line);
		line = NULL;
		if (!n)
			break ;
	}
	fclose(stream);
	return (0);
}
