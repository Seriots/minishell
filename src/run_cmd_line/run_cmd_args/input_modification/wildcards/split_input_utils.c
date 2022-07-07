/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 22:12:04 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/07 03:17:42 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	skip_quote_putwords(const char *s, int *position, char *quote)
{
	if (*quote == 0)
		*quote = s[(*position)];
	else
		*quote = 0;
}

void	skip_quote_letters(char quote, const char *s, int *i, int *count)
{
	if (s[*i] == quote)
	{
		*i += 1;
		while (s[*i] && s[*i] != quote)
		{
			*count += 1;
			*i += 1;
		}
		*count -= 1;
	}
}

void	skip_quote_words(const char *s, int *i)
{
	if (s[*i] == '\"')
	{
		*i += 1;
		while (s[*i] && s[*i] != '\"')
			*i += 1;
	}
	else if (s[*i] == '\'')
	{
		*i += 1;
		while (s[*i] && s[*i] != '\'')
			*i += 1;
	}
}
