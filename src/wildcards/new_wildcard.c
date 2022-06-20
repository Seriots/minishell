/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_wildcard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:07:28 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/20 22:17:18 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include "../../include/libft.h"
#include "../../include/ft_printf.h"
#include "../../include/list.h"
#include "../../include/minishell.h"

t_wildstr	*init_wildstr(char *str, t_wildstr *wildstr)
{
	wildstr->check_first = 0;
	wildstr->check_last = 0;
	wildstr->split = 0;
	if (str[0] != '*')
		wildstr->check_first = 1;
	if (str[ft_strlen(str) - 1] != '*')
		wildstr->check_last = 1;
	return (wildstr);
}

char	**treat_wildcards(char *str, char **args, int pos)
{
	t_wildstr	result;
	int			error;

	if (!str)
		return (0);
	error = ft_split_w(str, &result);
	if (error)
		return (0);
	return (result.split);
}

int	main(int argc, char *argv[])
{
	char	**str;
	int		i;

	str = 0;
	i = -1;
	if (argc >= 2)
		str = treat_wildcards(argv[2], &argv[1], 1);
	while (str[++i])
	{
		ft_printf("%s\n", str[i]);
		free (str[i]);
	}
	free(str);
	return (0);
}
