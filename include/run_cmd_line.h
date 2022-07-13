/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_line.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 02:06:46 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/13 23:34:05 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_CMD_LINE_H
# define RUN_CMD_LINE_H

# include <stddef.h>
# include "cmd_line.h"
# include "dict.h"
# include "shell.h"
# include "tree.h"

typedef int	(*t_run_cmd_node)(t_tree *, t_shell *);

int		run_cmd_and(t_tree *cmd_line, t_shell *shell);
int		run_cmd_args(t_tree *cmd_line, t_shell *shell);
int		run_cmd_line(t_tree *cmd_line, t_shell *shell);
int		run_cmd_or(t_tree *cmd_line, t_shell *shell);
int		run_cmd_pipe(t_tree *cmd_line, t_shell *shell);
int		run_pipeline(t_list *pipeline, t_shell *shell, int *pid);

/************************************************************/
/*						RUN_CMD_ARGS						*/
/************************************************************/

/*set_cmd_path.c*/
int		set_cmd_path(t_shell *shell, char **cmd);

/*check_in_path.c*/
int		check_in_path(t_dict *path, char **cmd);

/*all_redirections.c*/
int		manage_stdin(t_redir *redir, char **cmd_error);
int		manage_stdout(t_redir *redir, char **cmd_error);
int		manage_append_stdout(t_redir *redir, char **cmd_error);
int		manage_heredoc(t_redir *redir);
int		manage_stderr(t_redir *redir, char **cmd_error);

/*run_builtin.c*/
int		manage_redirections(t_tree *cmd_line, char **cmd_error);
int		backup_redirections(int fd_backup[3]);
int		manage_redirections_builtin(t_shell *shell, int fd_backup[3],
			t_tree *cmd_line);
int		get_my_builtin(char *name);
int		execute_builtin(t_shell *shell, t_tree *cmd);
int		execute_builtins(t_shell *shell, t_tree *cmd);
int		run_builtin(t_shell *shell, t_tree *cmd_line);

/*run_cmd_args.c*/
int		run_cmd_args(t_tree *cmd_line, t_shell *shell);

/**************************************************************/
/*                    INPUT_MODIFICATION                      */
/**************************************************************/
char	**split_with_quote(char	**input);
char	*remove_quotes(char *input);
int		all_redirs_modification(t_redir ***redirs_addr, t_shell *shell);
char	**input_modification(char **input, t_shell *shell);
char	*remove_quotes(char *input);
char	**removes_quotes(char **input);

/*question_mark.c*/
size_t	count_q_mark(size_t *i, char *return_value);
size_t	replace_q_mark(size_t *i, char **new, int size, char *return_value);

/*replace_special_args.c*/
char	*replace_special_char_heredoc(char *input, t_shell *shell);
char	*replace_special_char(char *input, t_shell *shell);
char	**replace_special_args(char **input, t_shell *shell);

/**************************************************************/
/*                          ENV_ARGS                          */
/**************************************************************/

/*env_arguments_utils*/
int		oppose_quote(int is_quoted);
char	*get_var(char *input, int pos);
size_t	get_size_var(char *var, t_dict *env);
size_t	concat_var(char *var, t_dict *env, char **result, size_t nb_letters);
int		ft_is_varchar(char c);

/*env_arguments.c*/
char	*get_env_arguments_heredoc(char *input, t_dict *env);
char	*get_env_arguments(char *input, t_dict *env);
char	**change_vars_in_args(char **args, t_dict *env);

#endif
