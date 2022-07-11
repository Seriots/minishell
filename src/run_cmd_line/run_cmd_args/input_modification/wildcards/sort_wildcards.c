/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_wildcards.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:07:20 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/11 17:32:21 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "list.h"

void	apply_default_sort(t_list **lst, t_list **start, t_list **pre)
{
	t_list	*wit;

	if (ft_strncmp((*lst)->content, (*lst)->next->content,
			ft_strlen((*lst)->content) + 1) > 0)
	{
		wit = (*lst)->next->next;
		if ((*pre))
			(*pre)->next = (*lst)->next;
		else
			*start = (*lst)->next;
		(*lst)->next->next = (*lst);
		(*lst)->next = wit;
		(*lst) = *start;
		(*pre) = 0;
	}
	else
	{
		(*pre) = (*lst);
		(*lst) = (*lst)->next;
	}
}

t_list	*default_sort(t_list *lst)
{
	t_list	*start;
	t_list	*pre;

	start = lst;
	pre = 0;
	while (lst->next)
		apply_default_sort(&lst, &start, &pre);
	return (start);
}

t_list	*sort_wildcard_result(t_list *lst)
{
	if (1)
		return (default_sort(lst));
}
