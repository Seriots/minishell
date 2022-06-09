/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argument.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 00:11:09 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/07 15:24:30 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "minishell.h"

char	*get_argument(const char *input, int input_size, int start)
{
	int		i;

	i = start;
	skip_argument(input, input_size, &i);
	if (i >= input_size)
		return (NULL);
//	Ce qui suit est a remplacer pour prendre en compte les variables $
//	Il ne faut pas toucher aux autres fonctions, bon courage
	return (ft_substr(input, start, i - start));
}
