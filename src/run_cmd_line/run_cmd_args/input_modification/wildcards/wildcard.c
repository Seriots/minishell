/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:07:28 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/07 13:00:20 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdlib.h>
#include "libft.h"
#include "list.h"
#include "minishell.h"

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
		{
			free(copy);
			return ;
		}
		list_add_back(result, new);
	}
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
			current->content = remove_quotes(current->content);
			pre = current;
			current = current->next;
		}
	}
}

char	**replace_args(char **argv)
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
			list_clear(&args, 0);
			ft_free_tab(argv);
			return (0);
		}
		list_add_back(&args, new);
		i ++;
	}
	complete_args(&args);
	free(argv);
	return (list_to_array(args));
}
