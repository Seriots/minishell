/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:47:44 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/13 20:55:23 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "list.h"
#include "wildcards.h"
#include <stdlib.h>

int	add_to_lst(t_list **lst_addr, char **array)
{
	t_list	*new;
	int		i;

	i = 0;
	while (array[i])
	{
		new = list_new(array[i]);
		if (!new)
			return (ft_free_tab(&array[i]), 1);
		list_add_back(lst_addr, new);
		i ++;
	}
	return (0);
}

char	**split_with_quote(char	**input)
{
	t_list	*list_input;
	char	**split_result;
	int		i;
	int		error;

	i = 0;
	list_input = 0;
	while (input[i])
	{
		split_result = ft_split_quoted(input[i], " ");
		if (!split_result)
			return (list_clear(&list_input, free), ft_free_tab(split_result), (void *)0);
		error = add_to_lst(&list_input, split_result);
		free(split_result);
		if (error)
			return (list_clear(&list_input, free), (void *)0);
		i ++;
	}
	return (list_to_array(list_input));
}