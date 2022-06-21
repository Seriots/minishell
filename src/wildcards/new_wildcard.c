/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_wildcard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:07:28 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/21 20:02:03 by lgiband          ###   ########.fr       */
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

t_wildstr	*init_wildstr(char *str, t_wildstr *wildstr)
{
	wildstr->check_first = 0;
	wildstr->check_last = 0;
	wildstr->split = 0;
	if (!str || ft_strlen(str) == 0)
		return(wildstr);
	if (str[0] != '*')
		wildstr->check_first = 1;
	if (str[ft_strlen(str) - 1] != '*')
		wildstr->check_last = 1;
	return (wildstr);
}

int	check_first_part(char *str, char *split, size_t *pos, size_t *pos_array)
{
	if (ft_strncmp(str, split, ft_strlen(split)) != 0)
		return (1);
	*pos += ft_strlen(split);
	*pos_array += 1;
	return (0);
}

int	check_middle_part(char *str, t_wildstr *split,
	size_t *pos, size_t *pos_array)
{
	while (str[*pos] && split->split[*pos_array]
		&& ((split->check_last && *pos_array != ft_arraylen(split->split) - 1)
			|| !split->check_last && *pos_array != ft_arraylen(split->split)))
	{
		if (ft_strncmp(&str[*pos], split->split[*pos_array],
				ft_strlen(split->split[*pos_array])) == 0)
		{	
			*pos += ft_strlen(split->split[*pos_array]) - 1;
			*pos_array += 1;
		}
		*pos += 1;
	}
	if (str[*pos] == 0
		&& ((split->check_last && *pos_array != ft_arraylen(split->split) - 1)
			|| *pos_array != ft_arraylen(split->split)))
		return (1);
	return (0);
}

int	check_last_part(char *str, char *split, size_t *pos, size_t *pos_array)
{
	while (str[*pos])
	{
		if (ft_strncmp(&str[*pos], split, ft_strlen(split) + 1) == 0)
		{
			*pos_array += 1;
			return (0);
		}
		*pos += 1;
	}
	return (1);
}

int	is_addable(char *d_name, t_wildstr *split)
{
	size_t		pos_array;
	size_t		pos;
	size_t		is_ok;

	if (!ft_arraylen(split->split))
		return (1);
	pos_array = 0;
	pos = 0;
	if (pos_array == 1)
		return (ft_strncmp(d_name, split->split[0], ft_strlen(d_name) + 1));
	if (split->check_first)
	{
		is_ok = check_first_part(d_name, split->split[0], &pos, &pos_array);
		if (is_ok)
			return (1);
	}
	is_ok = check_middle_part(d_name, split, &pos, &pos_array);
	if (is_ok)
		return (1);
	if (split->check_last)
	{
		is_ok = check_last_part(d_name,
				split->split[ft_arraylen(split->split) - 1], &pos, &pos_array);
		if (is_ok)
			return (1);
	}
	return (0);
}

void	add_to_result(t_list **result, char *elem, int hide_file)
{
	char	*copy;
	t_list	*new;
	int		i;

	if (!elem)
		return ;
	i = -1;
	if (!(hide_file == 0 && (elem[0] == '.')))
	{
		copy = ft_calloc(sizeof(char), ft_strlen(elem) + 1);
		if (!copy)
			return ;
		while (elem[++i])
			copy[i] = elem[i];
		new = list_new(copy);
		if (!new)
			return ;
		list_add_back(result, new);
	}
}

char	**list_to_array(t_list *result)
{
	int		nb_elem;
	char	**output;
	int		i;
	t_list	*pre;

	if (!result)
		return (0);
	i = 0;
	nb_elem = list_size(result);
	output = ft_calloc(sizeof(char *), nb_elem + 1);
	if (!output)
		return (0);
	while (result)
	{
		pre = result;
		output[i] = result->content;
		result = result->next;
		free(pre);
		i++;
	}
	return (output);
}

t_list	*replace_wildcards(char *str)
{
	DIR				*dir;
	struct dirent	*dire;
	int				hide_file;
	t_wildstr		split;
	t_list			*result;

	if (!str)
		return (0);
	if (ft_split_w(str, &split) == -1)
		return (0);
	hide_file = 0;
	result = 0;
	if (str[0] == '.')
		hide_file = 1;
	dir = opendir(".");
	dire = readdir(dir);
	while (dire)
	{
		if (!is_addable(dire->d_name, &split) || ft_strncmp(str, "*", 2) == 0)
			add_to_result(&result, dire->d_name, hide_file);
		dire = readdir(dir);
	}
	closedir(dir);
	ft_free_tab(split.split);
	return (result);
}

void	insert_wildcard_add(t_list **next, t_list **current,
		t_list **new, t_list **pre)
{
	*next = (*current)->next;
	*pre = list_last(*new);
	list_last(*new)->next = *next;
	list_delone(*current, free);
	*current = *next;
}

void	complete_args(t_list **args)
{
	t_list	*new;
	t_list	*next;
	t_list	*pre;
	t_list	*current;

	pre = 0;
	current = *args;
	while (current)
	{
		new = replace_wildcards(current->content);
		if (new)
		{
			if (pre == 0)
				*args = new;
			else
				pre->next = new;
			insert_wildcard_add(&next, &current, &new, &pre);
		}
		else
		{
			pre = current;
			current = current->next;
		}
	}
}

char	**replace_args(char *argv[])
{
	t_list	*args;
	t_list	*new;
	int		i;

	i = 0;
	args = 0;
	if (!argv)
		return (0);
	while (argv[i])
	{
		new = list_new(argv[i]);
		if (!new)
		{
			list_clear(&args, free);
			return (0);
		}
		list_add_back(&args, new);
		i ++;
	}
	complete_args(&args);
	return (list_to_array(args));
}

int	main(int argc, char *argv[])
{
	char	**str;
	int		i;
	char	**args;

	str = 0;
	i = -1;
	args = ft_calloc(sizeof(char *), 4);
	args[0] = ft_calloc(sizeof(char *), ft_strlen("'l'") + 1);
	args[1] = ft_calloc(sizeof(char *), ft_strlen("*Ma*k*f*le") + 1);
	args[2] = ft_calloc(sizeof(char *), ft_strlen("*e*") + 1);
	ft_strlcpy(args[0], "'l'", ft_strlen("'l'") + 1);
	ft_strlcpy(args[2], "*e*", ft_strlen("*e*") + 1);
	ft_strlcpy(args[1], "*Ma*k*f*le", ft_strlen("*Ma*k*f*le") + 1);
	str = replace_args(args);
	while (str[++i])
	{
		printf("%s\n", str[i]);
		free(str[i]);
	}
	free(args);
	free(str);
	return (0);
}
