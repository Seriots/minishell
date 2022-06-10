/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 20:03:47 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/10 11:22:44 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <signal.h>
# include "dict.h"
# include "tree.h"

# define SHELL_PROMPT "$> "

# define AND "&&"
# define OR "||"
# define PIPE "|"

# define REDIR_NBR 4
# define REDIR_STDIN "<"
# define REDIR_HEREDOC_STDIN "<<"
# define REDIR_STDOUT ">"
# define REDIR_APPEND_STDOUT ">>"

# define END_SEP "\t\n\v\f\r <>|&"
# define WHITESPACES "\t\n\v\f\r "

typedef struct s_std
{
	char	*pathfile;
	int		fd;
	int		fd_redir;
}	t_std;

typedef struct s_heredoc
{
	char	*end;
	int		fd;
}	t_heredoc;

typedef struct s_command
{
	char	**argv;
	t_list	*std;
	t_list	*heredoc;
}	t_command;

typedef struct s_shell
{
	t_dict	*env;
	t_dict	*export;
	char	*directory;
}	t_shell;

typedef int	(*t_set_redir)(t_command *, const char *, int, int);

/*
//	COMMANDS
*/
t_tree				*get_commands(t_shell *shell);

/*
//	SHELL
*/
/*free_shell.c*/
int					free_shell(t_shell *shell);

/*init_shell.c*/
t_dict				*getarg_env(char *line);
char     			*get_current_directory(void);
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
#endif
