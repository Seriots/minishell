/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 19:03:49 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/07 20:59:55 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/libft.h"
#include <unistd.h>
#include <stdlib.h>

static char     *get_space(char *str, size_t *length)
{
        char    *new_str;
        size_t  i;

        if (*length == 0)
                *length = 4096;
        else
                *length *= 2;
        new_str = ft_calloc(sizeof(char), *length + 1);
        if (!new_str)
                return (0);
        if (!str)
                return (new_str);
        i = -1;
        while(str[++i])
                new_str[i] = str[i];
        free(str);
        return (new_str);
}

char     *get_current_directory(void)
{
        char    *path;
        char    *try;
        size_t  length;

        length = 0;
        try = 0;
        path = 0;
        while (!try)
        {
                path = get_space(path, &length);
                if (!path)
                   return (0);
                try = getcwd(path, length);
        }
		length = ft_strlen(path);
		try = ft_calloc(sizeof(char), length);
		if (!try)
			return (0);
		ft_strlcpy(try, path, length + 1);
        free(path);
		return (try);
}

int     init_shell(t_shell *shell, char **env)
{
        shell->env = env;
        shell->directory = get_current_directory();
        if (shell->directory == 0)
                return (-1);
        return (0);
}
