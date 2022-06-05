/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:20:22 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/02 16:21:22 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstappend(t_list **lst, void *content)
{
	t_list	*elem;

	elem = ft_lstnew(content);
	if (!elem)
		return (-1);
	ft_lstadd_front(lst, elem);
	return (0);
}
