/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argument.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 00:11:09 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/07 01:26:01 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "minishell.h"

static void	set_sep_end(char **sep_end, const char *input, int input_size,
	int start)
{
	int	i;

	if (input[start] == '\"')
		*sep_end = "\"";
	else if (input[start] == '\'')
		*sep_end = "\'";
	else
		*sep_end = WHITESPACES;
	i = 0;
	while (start + i < input_size
		&& ft_strchr(*sep_end, input[start + i]) == NULL)
		i++;
	if (start + i == input_size)
		*sep_end = WHITESPACES;
}

char	*get_argument(const char *input, int input_size, int start)
{
	char	*sep_end;
	int		i;

	if (start >= input_size)
		return (NULL);
	set_sep_end(&sep_end, input, input_size, start);
	if (sep_end != WHITESPACES)
		start++;
//	Ce qui suit est a remplacer pour prendre en compte les variables $
//	Il ne faut pas toucher aux autres fonctions, bon courage
	i = 0;
	while (start + i < input_size
		&& ft_strchr(sep_end, input[start + i]) == NULL)
		i++;
	return (ft_substr(input, start, i));
}
