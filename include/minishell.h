/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 20:03:47 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/05 20:12:24 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SHELL_PROMPT "$> "

typedef struct s_shell
{
	char	**env;
}	t_shell;


void	free_commands(char **commands);
char	**get_commands(t_shell *shell);
int		run_commands(char **commands, t_shell *shell);

/*
//	SHELL
*/
int		free_shell(t_shell *shell);
int		init_shell(t_shell *shell, char **env);
int		run_shell(t_shell *shell);

#endif
