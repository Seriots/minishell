/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 20:03:47 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/06 23:14:52 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <signal.h>
# include "dict.h"
# include "read_cmd_line.h"
# include "tree.h"

# define _GNU_SOURCE

typedef struct s_wildstr
{
	char	**split;
	int		check_first;
	int		check_last;
}			t_wildstr;

typedef struct s_shell
{
	t_dict	*env;
	char	**env_str;
	t_dict	*export;
	char	*directory;
	int		return_value;
	int		(*builtins[7])(struct s_shell *shell, char **arguments);
}	t_shell;

typedef enum e_redir_tag
{
	to_stdin = redir_stdin,
	heredoc = redir_heredoc,
	to_stdout = redir_stdout,
	append_to_stdout = redir_append_stdout,
	to_stderr = redir_stderr
}	t_redir_tag;

typedef struct s_redir
{
	t_redir_tag	tag;
	union
	{
		char	*pathfile;
		struct
		{
			int		is_quoted;
			char	*heredoc;
		};
	};
}	t_redir;

typedef enum e_node_tag
{
	list_or,
	list_and,
	pipeline,
	args
}	t_node_tag;

typedef struct s_node
{
	t_node_tag	tag;
	char		**args;
	t_redir		**redirs;
}	t_node;

/**************************************************************/
/*                           SHELL                            */
/**************************************************************/
/*free_shell.c*/
int					free_shell(t_shell *shell);

/*init_envpath.c*/
int					add_envpath(t_dict **env, int *error);

/*init_shlvl.c*/
int					update_shlvl(t_dict **search, int *error);
int					add_shlvl(t_dict **env, int *error);

/*init_pwd.c*/
int					add_pwd(t_dict **env, int *error);
int					add_oldpwd(t_dict **env, int *error);

/*init_env_variable.c*/
int					free_and_set_error(char *key, char *value, int *error);

/*init_shell.c*/
int					set_default_variable(t_shell **shell);
t_dict				*getarg_env(char *line);
char				*get_current_directory(void);
int					init_shell(t_shell *shell, char **env);

/*run_shell.c*/
int					run_shell(t_shell *shell);

/**************************************************************/
/*                          SIGNAL                            */
/**************************************************************/

//	handle_signals.c
void				get_sig_heredoc(int sig, siginfo_t *siginfo, void *context);
void				get_sig(int sig, siginfo_t *siginfo, void *context);

//	init_sigact.c
struct sigaction	init_sigact_heredoc(void);
struct sigaction	init_sigact(void);

/**************************************************************/
/*                            RUN                             */
/**************************************************************/

/*set_cmd_path.c*/
int					set_cmd_path(t_shell *shell, char **cmd);

/*all_redirections.c*/
int					manage_stdin(t_redir *redir);
int					manage_stdout(t_redir *redir);
int					manage_append_stdout(t_redir *redir);
int					manage_heredoc(t_redir *redir);
int					manage_stderr(t_redir *redir);

/*run_cmd_args.c*/
int					run_cmd_args(t_tree *cmd_line, t_shell *shell);

/**************************************************************/
/*                          BUILTINS                          */
/**************************************************************/
int					cd_command(t_shell *shell, char **arguments);
int					echo_command(t_shell *shell, char **arguments);
int					export_command(t_shell *shell, char **arguments);
int					exit_command(t_shell *shell, char **arguments);
int					env_command(t_shell *shell, char **arguments);
int					unset_command(t_shell *shell, char **arguments);
int					pwd_command(t_shell *shell, char **arguments);

/*run_builtin.c*/
int					manage_redirections(t_tree *cmd_line);
int					backup_redirections(int fd_backup[3]);
int					manage_redirections_builtin(t_shell *shell,
						int fd_backup[3], t_tree *cmd_line);
int					get_my_builtin(char *name);
int					execute_builtin(t_shell *shell, t_tree *cmd);
int					execute_builtins(t_shell *shell, t_tree *cmd);
int					run_builtin(t_shell *shell, t_tree *cmd_line);

/*init_builtins.c*/
void				init_builtins(t_shell **shell);

/*cd_utils.c*/
void				print_error_message_cd(char *path);
char				*ft_malloc_str(const char *str);
int					update_pwd(t_shell **shell, char *path);

/*export_utils.c*/
int					init_export_copy(t_shell *shell, t_dict **copy,
						t_dict **export_copy);
int					print_export(t_shell *shell);
int					invalid_identifier_export(char *arg);
int					check_key(char *arg);
int					check_value(char *arg);

/**************************************************************/
/*                         WILDCARDS                          */
/**************************************************************/

/*split_input_utils.c*/
void				skip_quote_putwords(const char *s,
						int *position, char *quote);
void				skip_quote_letters(char quote, const char *s,
						int *i, int *count);
void				skip_quote_words(const char *s, int *i);

/*split_input.c*/
int					ft_split_w(char *str, t_wildstr *wildstr);

/*check_part.c*/
int					check_last_part(char *str, char *split,
						size_t *pos, size_t *pos_array);
int					check_middle_part(char *str, t_wildstr *split,
						size_t *pos, size_t *pos_array);
int					check_first_part(char *str, char *split,
						size_t *pos, size_t *pos_array);

/*wildcards_utils.c*/
int					is_addable(char *d_name, t_wildstr *split);
t_wildstr			*init_wildstr(char *str, t_wildstr *wildstr);
char				**list_to_array(t_list *result);
void				insert_wildcard_add(t_list **next, t_list **current,
						t_list **new, t_list **pre);

/*wildcards.c*/
t_wildstr			*init_wildstr(char *str, t_wildstr *wildstr);
int					treat_wildcards(char *str, char **args,
						int pos, t_wildstr *result);
t_list				*replace_wildcards(char *str);
char				**replace_args(char **argv);

/**************************************************************/
/*                          ENV_ARGS                          */
/**************************************************************/

/*env_arguments_utils*/
int					oppose_quote(int is_quoted);
char				*get_var(char *input, int pos);
size_t				get_size_var(char *var, t_dict *env);
size_t				concat_var(char *var, t_dict *env,
						char **result, size_t nb_letters);
int					ft_is_varchar(char c);

/*env_arguments.c*/
char				**change_vars_in_args(char **args, t_dict *env);

/**************************************************************/
/*                      SPECIAL_CHAR                          */
/**************************************************************/

/*question_mark.c*/
size_t				count_q_mark(size_t *i, char *return_value);
size_t				replace_q_mark(size_t *i, char **new,
						int size, char *return_value);

/*replace_special_args.c*/
char				**replace_special_args(char **input, t_shell *shell);

/**************************************************************/
/*                    INPUT_MODIFICATION                      */
/**************************************************************/
char				*remove_quotes(char *input);
char				**input_modification(char **input, t_shell *shell);
char				*remove_quotes(char *input);
char				**removes_quotes(char **input);

/**************************************************************/
/*                     CHECKER_BUILTINS                       */
/**************************************************************/
void				export_checker(int argc, char *argv[], char **env);
void				echo_checker(int argc, char *argv[], char **env);
void				cd_checker(int argc, char *argv[], char **env);
void				unset_checker(int argc, char *argv[], char **env);

void				free_cmd_line(void *node_addr);
#endif
