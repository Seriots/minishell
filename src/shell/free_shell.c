/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 19:04:23 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/09 20:42:55 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdlib.h>

int	free_shell(t_shell *shell)
{
	free(shell->directory);
	dict_clear(shell->env, free, free);
	dict_clear(shell->export, free, free);
	return (0);
}
