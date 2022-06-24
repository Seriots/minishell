/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 20:03:47 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/24 18:00:55 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <signal.h>
# include "dict.h"
# include "tree.h"

# define _GNU_SOURCE

# define SHELL_PROMPT "$> "

# define AND "&&"
# define OR "||"
# define PIPE "|"

# define REDIR_NBR 4
# define REDIR_STDIN "<"
# define REDIR_STDOUT ">"
# define REDIR_STDERR "2>"
# define REDIR_APPEND_STDOUT ">>"
# define REDIR_HEREDOC "<<"

# define END_SEP "\t\n\v\f\r <>|&"
# define END_SEP_NOT_WSPACE "<>|&"
# define WHITESPACES "\t\n\v\f\r "

typedef struct s_wildstr
{
	char	**split;
	int		check_first;
	int		check_last;
}			t_wildstr;

typedef struct s_std
{
	char	*pathfile;
	int		fd;
	int		fd_redir;
	int		append;
	char	*end;
	int		heredoc;
}	t_std;

typedef struct s_command
{
	char	**argv;
	t_list	*std;
}	t_command;

typedef struct s_pipes
{
	int	*back;
	int	*front;
}	t_pipes;

typedef struct s_shell
{
	t_dict	*env;
	char	**env_str;
	t_dict	*export;
	char	*directory;
	int		(*builtins[7])(struct s_shell *shell, char **arguments);
}	t_shell;

typedef int	(*t_set_redir)(t_command *, const char *, int, int);

/**************************************************************/
/*                          COMMANDS                          */
/**************************************************************/
void				free_argv(void *argv_addr);
void				free_command(void *command);
void				free_commands(t_tree *commands);
void				free_std(void *std_addr);

//	get_commands
t_command			*get_bzero_command(void);
t_command			*get_command(const char *input, int input_size);
t_tree				*get_commands(t_shell *shell);
t_tree				*parse_input(const char *input, int input_size);
t_tree				*parse_input_and(const char *input, int input_size);
t_tree				*parse_input_brackets(const char *input, int input_size);
t_tree				*parse_input_or(const char *input, int input_size);
t_tree				*parse_input_pipe(const char *input, int input_size);
t_tree				*parse_input_simple(const char *input, int input_size);
int					set_arguments(t_command *cmd, const char *input,
						int input_size);
int					set_redirections(t_command *cmd, const char *input,
						int input_size);

int					count_arguments(const char *input, int input_size);
int					count_redirections(const char *input, int input_size);
char				*get_argument(const char *input, int input_size, int start);
char				*get_argument_after(const char *arg, const char *input,
						int input_size);
int					is_argument_equal_to(const char *arg, const char *input,
						int input_size, int start);
int					is_argument_in_input(const char *arg, const char *input,
						int input_size);
int					is_argument_sep(const char *input, int input_size,
						int start);
int					is_between_brackets(const char *input, int input_size);
int					is_sep_equal_to(const char *sep, const char *input,
						int input_size, int start);
void				skip_argument(const char *input, int input_size, int *i);
void				skip_redirections(const char *input, int input_size,
						int *i);
void				skip_sep(const char *input, int input_size, int *i);
void				skip_to(const char *arg, const char *input, int input_size,
						int *i);
void				skip_to_next_argument(const char *input, int input_size,
						int *i);
void				skip_whitespaces(const char *input, int input_size, int *i);

//	run_commands
void				free_pipes_and_pids(int **pipe_fd, int *pid,
						int nb_sub_commands);
int					fork_and_run_sub_commands(t_list *sub_commands,
						t_shell *shell, int *pid);
int					init_pipes_and_pids(int ***pipe_fd, int **pid,
						int nb_sub_commands);
int					run_command(t_command *command, t_shell *shell);
int					run_commands(t_tree *commands, t_shell *shell);
int					run_pipe_commands(t_tree *commands, t_shell *shell);
int					run_tree_commands(t_tree *commands, t_shell *shell);
int					set_heredocs(t_tree *commands, t_shell *shell);

/**************************************************************/
/*                           SHELL                            */
/**************************************************************/
/*free_shell.c*/
int					free_shell(t_shell *shell);

/*init_shell.c*/
int					set_default_variable(t_shell **shell);
t_dict				*getarg_env(char *line);
char				*get_current_directory(void);
int					init_shell(t_shell *shell, char **env);

/*run_shell.c*/
int					run_shell(t_shell *shell);

/*
// SIGNALS
*/

//	handle_signals.c
void				get_sig(int sig, siginfo_t *siginfo, void *context);

//	init_sigact.c
struct sigaction	init_sigact(void);

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

/*init_builtins.c*/
void				init_builtins(t_shell **shell);

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
void				skip_quote_putwords(const char *s, int *position, char *quote);
void				skip_quote_letters(char quote, const char *s, int *i, int *count);
void				skip_quote_words(const char *s, int *i);

/*split_input.c*/
int					ft_split_w(char *str, t_wildstr *wildstr);
static int			get_nb_words(char const *s, char c);
static char			*ft_put_word(char const *s, char c, int *position);
static int			ft_count_letters(char const *s, char c, int *position);

/*check_part.c*/
int					check_last_part(char *str, char *split, size_t *pos, size_t *pos_array);
int					check_middle_part(char *str, t_wildstr *split,
						size_t *pos, size_t *pos_array);
int					check_first_part(char *str, char *split, size_t *pos, size_t *pos_array);

/*wildcards_utils.c*/
int					is_addable(char *d_name, t_wildstr *split);
t_wildstr			*init_wildstr(char *str, t_wildstr *wildstr);
char				**list_to_array(t_list *result);
void				insert_wildcard_add(t_list **next, t_list **current,
						t_list **new, t_list **pre);

/*wildcards.c*/
t_wildstr			*init_wildstr(char *str, t_wildstr *wildstr);
int					treat_wildcards(char *str, char **args, int pos, t_wildstr *result);
t_list				*replace_wildcards(char *str);
char				**replace_args(char **argv);

/**************************************************************/
/*                          ENV_ARGS                          */
/**************************************************************/

/*env_arguments_utils*/
int					oppose_quote(int is_quoted);
char				*get_var(char *input, int pos);
size_t				get_size_var(char *var, t_dict *env);
size_t				concat_var(char *var, t_dict *env, char **result, size_t nb_letters);
int					ft_is_varchar(char c);

/*env_arguments.c*/
char				**change_vars_in_args(char **args, t_dict *env);

/**************************************************************/
/*                    INPUT_MODIFICATION                      */
/**************************************************************/

char				**input_modification(char **input, t_dict *dict);
#endif
