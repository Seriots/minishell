/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 19:04:23 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/07 03:57:06 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "dict.h"
#include "libft.h"
#include "minishell.h"

int	free_shell(t_shell *shell)
{
	free(shell->directory);
	ft_free_tab(shell->env_str);
	dict_clear(shell->env, free, free);
	dict_clear(shell->export, free, free);
	return (0);
}
