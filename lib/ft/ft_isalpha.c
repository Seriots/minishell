/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:08:29 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/05/02 14:21:28 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	int	is_alpha;

	is_alpha = (c >= 'a' && c <= 'z');
	is_alpha |= (c >= 'A' && c <= 'Z');
	return (is_alpha);
}
