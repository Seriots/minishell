/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:49:06 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/08 11:49:22 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_end_quoted(const char *end)
{
	int	count_quote;
	int	count_double_quote;

	count_quote = 0;
	count_double_quote = 0;
	while (*end)
	{
		if (*end == '\'')
			count_quote++;
		if (*end == '\"')
			count_double_quote++;
		end++;
	}
	return (count_quote >= 2 || count_double_quote >= 2);
}

void	remove_quotes_onplace(char *end)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (end[i])
	{
		if (end[i] == '\'')
		{
			i++;
			while (end[i++] != '\'')
				end[j++] = end[i];
		}
		else if (end[i] == '\'')
		{
			i++;
			while (end[i++] != '\'')
				end[j++] = end[i];
		}
		else
			end[j++] = end[i++];
	}
}
