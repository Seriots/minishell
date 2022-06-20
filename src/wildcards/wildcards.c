/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:12:00 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/20 15:45:49 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../include/libft.h"
#include "../../include/ft_printf.h"
#include "../../include/list.h"
#include "../../include/minishell.h"

/*
* Take a str in parameters and return a str with all corresponding str in the current directory.
* if no correspondance is found, input is return.
*/
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

void	copy_lst_in_str(t_list *wildcards, char *result, size_t size_max)
{
	if (!wildcards)
		return ;
	while (wildcards)
	{
		ft_strlcat(result, wildcards->content, size_max + 1);
		if (wildcards->next != 0)
			ft_strlcat(result, " ", size_max + 1);
		wildcards = wildcards->next;
	}
}

char	*wild_str(t_list *wildcards, char *input)
{
	size_t	size_max;
	char	*result;

	if (!wildcards)
	{
		if (ft_strlen(input) == 0)
			return (0);
		result = ft_calloc(sizeof(char), ft_strlen(input) + 1);
		if (!result)
			return (0);
		ft_strlcpy(result, input, ft_strlen(input) + 1);
		return (result);
	}
	size_max = list_size(wildcards) - 1;
	size_max += get_size_list_contents(wildcards);
	result = ft_calloc(sizeof(char), size_max + 1);
	if (!result)
		return (0);
	copy_lst_in_str(wildcards, result, size_max);
	list_clear(&wildcards, free);
	return (result);
}

int	check_directory(struct dirent *directory, char *input,
	int hide_file, t_list **wildcards)
{
	char	*name_copy;

	name_copy = ft_calloc(sizeof(char), ft_strlen(directory->d_name) + 1);
	if (!name_copy)
		return (-1);
	ft_strlcpy(name_copy, directory->d_name,
		ft_strlen(directory->d_name) + 1);
	if (directory && is_wildcard_comp(input, directory->d_name))
	{
		if (!(hide_file == 0 && directory->d_name[0] == '.'))
			list_add_back(wildcards, list_new(name_copy));
		else
			free(name_copy);
	}
	else
		free(name_copy);
	return (0);
}

char	*replace_wildcard(char *input)
{
	DIR				*dir;
	struct dirent	*directory;
	int				hide_file;
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
		if (check_directory(directory, input, hide_file, &wildcards))
		{
			list_clear(&wildcards, free);
			return (0);
		}
		directory = readdir(dir);
	}
	closedir(dir);
	return (wild_str(wildcards, input));
}

/*
int	main(int argc, char *argv[])
{
	char	*str;

	str = 0;
	if (argc == 2)
		str = replace_wildcard(argv[1]);
	ft_printf("%s\n", str);
	free (str);
	return (0);
}*/
