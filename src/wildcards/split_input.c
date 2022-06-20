/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 22:11:30 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/20 22:14:16 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include "../../include/libft.h"
#include "../../include/ft_printf.h"
#include "../../include/list.h"
#include "../../include/minishell.h"

static int	ft_count_letters(char const *s, char c, int *position)
{
	int	i;
	int	count;

	i = *position;
	count = 0;
	while (s[i] && s[i] == c)
	{
		i++;
		*position += 1;
	}
	while (s[i] && s[i] != c)
	{
		skip_quote_letters('\"', s, &i, &count);
		skip_quote_letters('\'', s, &i, &count);
		if (s[i])
		{
			i++;
			count ++;
		}
	}
	return (count);
}

static char	*ft_put_word(char const *s, char c, int *position)
{
	int		nb_letters;
	char	*result;
	char	quote;
	int		i;

	i = 0;
	quote = 0;
	nb_letters = ft_count_letters(s, c, position);
	result = (char *)malloc(sizeof(char) * (nb_letters + 1));
	if (!result)
		return (0);
	result[nb_letters] = 0;
	while (i < nb_letters)
	{
		if ((s[(*position)] == '\"' || s[(*position)] == '\'')
			&& (quote == 0 || quote == s[(*position)]))
			skip_quote_putwords(s, position, &quote);
		else
			result[i++] = s[(*position)];
		*position += 1;
	}
	if (s[(*position)] == '\"' || s[(*position)] == '\'')
		*position += 1;
	return (result);
}

static int	get_nb_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			count ++;
			while (s[i] && s[i] != c)
			{
				skip_quote_words(s, &i);
				if (s[i])
					i++;
			}
		}
	}
	return (count);
}

int	ft_split_w(char *str, t_wildstr *wildstr)
{
	char			**split_result;
	unsigned int	nb_words;
	int				i;
	int				pos;

	if (!str)
		return (-1);
	wildstr = init_wildstr(str, wildstr);
	nb_words = get_nb_words(str, '*');
	ft_printf("%d\n", nb_words);
	split_result = (char **)malloc(sizeof(char *) * (nb_words + 1));
	if (!split_result)
		return (0);
	split_result[nb_words] = 0;
	i = 0;
	pos = 0;
	while (i < nb_words)
	{
		split_result[i] = ft_put_word(str, '*', &pos);
		i++;
	}
	wildstr->split = split_result;
	return (0);
}
