/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woutcase_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:06:05 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/12 16:09:24 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "list.h"

static int	ft_strncmp_woutcase(char *s1, char *s2, size_t n)
{
	size_t	i;

	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (1);
	if (n == 0)
		return (0);
	i = 0;
	while (i + 1 < n && ft_tolower(s1[i]) && ft_tolower(s2[i])
		&& ft_tolower(s1[i]) == ft_tolower(s2[i]))
		i++;
	return ((unsigned char) ft_tolower(s1[i])
		- (unsigned char) ft_tolower(s2[i]));
}

void	apply_woutcase_sort(t_list **lst, t_list **start, t_list **pre)
{
	t_list	*wit;

	if (ft_strncmp_woutcase((*lst)->content, (*lst)->next->content,
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

t_list	*woutcase_sort(t_list *lst)
{
	t_list	*start;
	t_list	*pre;

	start = lst;
	pre = 0;
	while (lst->next)
		apply_woutcase_sort(&lst, &start, &pre);
	return (start);
}
