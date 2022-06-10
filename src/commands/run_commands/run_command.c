/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:27:04 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/10 20:56:57 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "dict.h"
#include "libft.h"
#include "minishell.h"

static char	*get_path_exec(char *argv0, t_dict *env)
{
	char	*path;
	char	**dir_exec;
	char	*d_exec;
	char	*path_exec;
	int		i;

	(void) env;
	path = getenv("PATH");
	if (!path)
		return (NULL);
	dir_exec = ft_split(path, ':');
	if (!dir_exec)
		return (NULL);
	i = 0;
	while (dir_exec[i])
	{
		d_exec = ft_strjoin(dir_exec[i], "/");
		if (!d_exec)
		{
			free_argv(dir_exec);
			return (NULL);
		}
		path_exec = ft_strjoin(d_exec, argv0);
		free(d_exec);
		if (!path_exec)
		{
			free_argv(dir_exec);
			return (NULL);
		}
		if (!access(path_exec, X_OK))
			break ;
		free(path_exec);
		i++;
	}
	if (!dir_exec[i])
		path_exec = NULL;
	free_argv(dir_exec);
	return (path_exec);
}

static void	run_command_in_child(t_command *command, t_shell *shell)
{
	t_std	*std;
	char	*path_exec;
	int		return_value;

	while (command->std)
	{
		std = command->std->content;
		if (!std->heredoc && std->fd_redir == 0)
			std->fd = open(std->pathfile, O_RDONLY);
		if (!std->heredoc && std->fd_redir == 1 && std->append == 0)
			std->fd = open(std->pathfile, O_WRONLY | O_CREAT, S_IRUSR
					| S_IWUSR | S_IRGRP | S_IROTH);
		if (!std->heredoc && std->fd_redir == 1 && std->append == 1)
			std->fd = open(std->pathfile, O_WRONLY | O_APPEND | O_CREAT,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (std->fd == -1)
			exit(-1);
		return_value = dup2(std->fd, std->fd_redir);
		close(std->fd);
		command->std = command->std->next;
	}
	path_exec = get_path_exec(command->argv[0], shell->env);
	if (!path_exec)
		exit(-1);
	return_value = execve(path_exec, command->argv, shell->env_str);
	exit(return_value);
}

int	run_command(t_command *command, t_shell *shell)
{
	int	pid;
	int	wstatus;

	pid = fork();
	if (pid == -1)
	{
		return (-1);
	}
	if (pid == 0)
		run_command_in_child(command, shell);
	waitpid(pid, &wstatus, 0);
	if (!WIFEXITED(wstatus))
		return (-1);
	return (WEXITSTATUS(wstatus));
}
