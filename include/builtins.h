/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 19:44:28 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/10 21:47:57 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "dict.h"
# include "shell.h"

int		cd_command(t_shell *shell, char **arguments);
int		echo_command(t_shell *shell, char **arguments);
int		export_command(t_shell *shell, char **arguments);
int		exit_command(t_shell *shell, char **arguments);
int		env_command(t_shell *shell, char **arguments);
int		unset_command(t_shell *shell, char **arguments);
int		pwd_command(t_shell *shell, char **arguments);

/*cd_utils.c*/
void	print_error_message_cd(char *path);
char	*ft_malloc_str(const char *str);
int		update_pwd(t_shell **shell, char *path);

/*export_utils.c*/
int		init_export_copy(t_shell *shell, t_dict **copy,
			t_dict **export_copy);
int		print_export(t_shell *shell);
int		invalid_identifier_export(char *arg);
int		check_key(char *arg);
int		check_value(char *arg);

#endif
