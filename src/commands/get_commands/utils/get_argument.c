/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argument.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 00:11:09 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/10 20:30:13 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include "minishell.h"

char	*get_argument(const char *input, int input_size, int start)
{
	int		i;

//	Cette fonction est a remplacer pour prendre en compte les variables $
//	et pour enlever les " et ' en doubles
//	Il ne faut pas toucher aux autres fonctions, bon courage
	i = start;
	skip_argument(input, input_size, &i);
	return (ft_substr(input, start, i - start));
}
