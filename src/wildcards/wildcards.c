/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:12:00 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/16 23:02:47 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../include/libft.h"
#include "../../include/ft_printf.h"
#include "../../include/list.h"

int	get_next_str(char *str, unsigned int pos)
{
	unsigned int	i;

	while (str[pos] && str[pos] != '*')
		pos ++;
	while (str[pos] && str[pos] == '*')
		pos ++;
	if (!str[pos])
		return (-1);
	i = 1;
	while (str[pos + i])
	{
		if (str[pos + i] == '*')
			return (pos);
		i++;
	}
	return (-1);
}

char	*get_substr(char *str, unsigned int pos)
{
	unsigned int	length;
	char			*result;
	unsigned int	i;

	length = 0;
	while (str[pos + length] && str[pos + length] != '*')
		length ++;
	if (!str[pos + length])
		return (0);
	result = ft_calloc(sizeof(char), length + 1);
	if (!result)
		return (0);
	i = 0;
	while (i < length)
	{
		result[i] = str[pos + i];
		i ++;
	}
	return (result);
}

unsigned int	is_substr(char *input, unsigned int pos, char *substr)
{
	unsigned int	i;

	if (!substr)
		return (0);
	if (!substr[0])
		return (1);
	i = 0;
	while (substr[i])
	{
		if (input[pos + i] != substr[i])
			return (0);
		i ++;
	}
	return (i);
}

int	comp(char *s1, char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i ++;
	return (s1[i] != s2[i]);
}

int	check_first_part(char *input, char *name)
{
	unsigned int	i;

	i = 0;
	if (input[i] == '*')
		return (1);
	while (input[i] && name[i] && input[i] != '*')
	{
		if (input[i] != name[i])
			return (0);
		i ++;
	}
	if (input[i] == '*' && input[i - 1] == name[i - 1])
		return (1);
	if (input[i] == name[i])
		return (1);
	else
		return (0);
}

int	check_last_part(char *input, char *name, unsigned int last_pos)
{
	size_t	i;
	size_t	size_input;
	size_t	size_name;

	if (last_pos != 0)
		name[last_pos - 1] = 0;
	i = 0;
	name = &name[last_pos];
	size_input = ft_strlen(input);
	size_name = ft_strlen(name);
	if (input[size_input - i - 1] == '*')
		return (1);
	while (size_input - i && size_name - i && input[size_input - i - 1] != '*')
	{
		if (input[size_input - i - 1] != name[size_name - i - 1])
			return (0);
		i ++;
	}
	if (input[size_input - i - 1] == '*' && input[size_input - i]
		== name[size_name - i])
		return (1);
	if (input[size_input - i - 1] == name[size_name - i - 1])
		return (1);
	else
		return (0);
}

int	check_middle_part(char *input, char *name,
	unsigned int *position, int *next_str)
{
	char	*substr;

	substr = get_substr(input, *next_str);
	if (!substr)
		return (0);
	while (name[*position] && comp(&name[*position], substr, ft_strlen(substr)))
		*position += 1;
	if (name[*position])
	{
		*position += ft_strlen(substr);
		*next_str = get_next_str(input, *next_str);
	}
	free(substr);
	return (1);
}

int	is_wildcard_comp(char *input, char *name)
{
	unsigned int	position;
	unsigned int	last_pos;
	int				next_str;

	if (!input || !name)
		return (0);
	next_str = get_next_str(input, 0);
	position = 0;
	if (!check_first_part(input, name))
		return (0);
	while (name[position] && input[position] != '*')
		position ++;
	last_pos = position;
	while (name[position] && next_str != -1)
	{
		if (!check_middle_part(input, name, &position, &next_str))
			return (0);
		last_pos = position;
	}
	if (!check_last_part(input, name, last_pos))
		return (0);
	if (next_str == -1)
		return (1);
	return (0);
}

size_t	get_size_list_contents(t_list *wildcards)
{
	size_t	size;

	size = 0;
	while (wildcards)
	{
		size += ft_strlen(wildcards->content);
		wildcards = wildcards->next;
	}
	return (size);
}

char	*wild_str(t_list *wildcards, char *input)
{
	size_t	size_max;
	t_list	*copy;
	char	*result;

	if (!wildcards)
	{
		result = ft_calloc(sizeof(char), ft_strlen(input) + 1);
		if (!result)
			return (0);
		ft_strlcpy(result, input, ft_strlen(input) + 1);
		return (result);
	}
	copy = wildcards;
	size_max = list_size(wildcards) - 1;
	size_max += get_size_list_contents(wildcards);
	result = ft_calloc(sizeof(char), size_max + 1);
	if (!result)
		return (0);
	while (wildcards)
	{
		ft_strlcat(result, wildcards->content, size_max + 1);
		if (wildcards->next != 0)
			ft_strlcat(result, " ", size_max + 1);
		wildcards = wildcards->next;
	}
	list_clear(&copy, free);
	return (result);
}

char	*replace_wildcard(char *input)
{
	DIR				*dir;
	struct dirent	*directory;
	int				hide_file;
	char			*name_copy;
	t_list			*wildcards;

	if (!input)
		return (0);
	hide_file = 0;
	wildcards = 0;
	if (input[0] == '.')
		hide_file = 1;
	dir = opendir(".");
	directory = readdir(dir);
	while (directory)
	{
		name_copy = ft_calloc(sizeof(char), ft_strlen(directory->d_name) + 1);
		if (!name_copy)
			return (0);
		ft_strlcpy(name_copy, directory->d_name,
			ft_strlen(directory->d_name) + 1);
		if (directory && is_wildcard_comp(input, directory->d_name))
		{
			if (!(hide_file == 0 && directory->d_name[0] == '.'))
				list_add_back(&wildcards, list_new(name_copy));
			else
				free(name_copy);
		}
		else
			free(name_copy);
		directory = readdir(dir);
	}
	closedir(dir);
	return (wild_str(wildcards, input));
}

int	main(int argc, char *argv[])
{
	char	*str;

	if (argc == 2)
		str = replace_wildcard(argv[1]);
	ft_printf("%s\n", str);
	free (str);
	return (0);
}
