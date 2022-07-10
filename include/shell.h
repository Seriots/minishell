/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 19:37:37 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/10 23:11:37 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "dict.h"
# include "shell.h"

typedef enum e_shell_status
{
	reading_cmd_line,
	parsing_cmd_line,
	running_cmd_line,
	terminating_shell
}	t_shell_status;

typedef struct s_shell
{
	t_dict	*env;
	char	**env_str;
	t_dict	*export;
	char	*directory;
	char	*input;
	char	*cmd_line_input;
	int		return_value;
	int		(*builtins[7])(struct s_shell *shell, char **arguments);
}	t_shell;

/*free_shell.c*/
int		free_shell(t_shell *shell);

/*init_builtins.c*/
void	init_builtins(t_shell **shell);

/*init_envpath.c*/
int		add_envpath(t_dict **env, int *error);

/*init_shlvl.c*/
int		update_shlvl(t_dict **search, int *error);
int		add_shlvl(t_dict **env, int *error);

/*init_signals.c*/
void	init_signals(void);

/*init_pwd.c*/
int		add_pwd(t_dict **env, int *error);
int		add_oldpwd(t_dict **env, int *error);

/*init_env_variable.c*/
int		free_and_set_error(char *key, char *value, int *error);

/*init_shell.c*/
int		set_default_variable(t_shell **shell);
t_dict	*getarg_env(char *line);
char	*get_current_directory(void);
int		init_shell(t_shell *shell, char **env);

/*run_shell.c*/
int		run_shell(t_shell *shell);

#endif
