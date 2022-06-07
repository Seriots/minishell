/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 20:03:47 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/07 15:30:54 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <signal.h>
# include "libft.h"

# define SHELL_PROMPT "$> "

# define AND "&&"
# define OR "||"
# define PIPE "|"

# define REDIR_NBR 4
# define REDIR_STDIN "<"
# define REDIR_HEREDOC_STDIN "<<"
# define REDIR_STDOUT ">"
# define REDIR_APPEND_STDOUT ">>"

# define END_SEP "\t\n\v\f\r <>"
# define WHITESPACES "\t\n\v\f\r "

typedef struct s_command
{
	char	*exec_path;
	char	**argv;

	int		redir_stdin;
	char	*pathfile_stdin;
	int		heredoc_stdin;
	char	*end_heredoc;
	int		redir_stdout;
	int		redir_append_stdout;
	char	*pathfile_stdout;
}	t_command;

typedef struct s_shell
{
	char	**env;
}	t_shell;

typedef int	(*t_set_redir)(t_command *, const char *, int);

/*
//	COMMANDS
*/
void				free_command(void *command_addr);
void				free_commands(t_tree *commands);
t_tree				*get_commands(t_shell *shell);
int					run_commands(char **commands, t_shell *shell);

//	parse_input
int					contain_and(const char *input, int input_size);
int					contain_or(const char *input, int input_size);
int					contain_pipe(const char *input, int input_size);
int					is_between_brackets(const char *input, int input_size);
t_tree				*parse_input(const char *input, int input_size);
t_tree				*parse_input_and(const char *input, int input_size);
t_tree				*parse_input_brackets(const char *input, int input_size);
t_tree				*parse_input_or(const char *input, int input_size);
t_tree				*parse_input_pipe(const char *input, int input_size);
t_tree				*parse_input_simple(const char *input, int input_size);

//	get_command
char				*get_argument(const char *input, int input_size, int start);
t_command			*get_bzero_command(void);
t_command			*get_command(const char *input, int input_size);
int					set_arguments(t_command *cmd, const char *input,
						int input_size);
int					set_redirections(t_command *cmd, const char *input,
						int input_size);

int					count_arguments(const char *input, int input_size);
int					count_redirections(const char *input, int input_size);
char				*get_argument_after(const char *arg, const char *input,
						int input_size);
int					is_argument_equal_to(const char *arg, const char *input,
						int input_size, int start);
int					is_argument_in_input(const char *arg, const char *input,
						int input_size);
int					is_argument_redirection(const char *input, int input_size,
						int start);
void				skip_argument(const char *input, int input_size, int *i);
void				skip_redirection(const char *input, int input_size, int *i);
void				skip_redirections(const char *input, int input_size, int *i);
void				skip_to(const char *arg, const char *input, int input_size,
						int *i);
void				skip_to_next_argument(const char *input, int input_size,
						int *i);
void				skip_whitespaces(const char *input, int input_size, int *i);

/*
//	SHELL
*/
int					free_shell(t_shell *shell);
int					init_shell(t_shell *shell);
int					run_shell(t_shell *shell);

/*
// SIGNALS
*/

//	handle_signals.c
void				get_sig(int sig, siginfo_t *siginfo, void *context);

//	init_sigact.c
struct sigaction	init_sigact(void);
#endif
