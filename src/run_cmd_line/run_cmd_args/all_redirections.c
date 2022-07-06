/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 23:10:41 by lgiband           #+#    #+#             */
/*   Updated: 2022/07/06 23:01:26 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int	manage_stdin(t_redir *redir)
{
	int	fd;
	int	ret_value;

	fd = open(redir->pathfile, O_RDONLY);
	if (fd == -1)
		return (-1);
	ret_value = dup2(fd, 0);
	close(fd);
	return (ret_value);
}

int	manage_stdout(t_redir *redir)
{
	int	fd;
	int	ret_value;

	fd = open(redir->pathfile, O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		return (-1);
	ret_value = dup2(fd, 1);
	close(fd);
	return (ret_value);
}

int	manage_append_stdout(t_redir *redir)
{
	int	fd;
	int	ret_value;

	fd = open(redir->pathfile, O_CREAT | O_WRONLY | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd <= -1)
		return (fd);
	ret_value = dup2(fd, 1);
	close(fd);
	return (ret_value);
}

int	manage_heredoc(t_redir *redir)
{
	int	pipefd[2];
	int	ret_value;

	if (pipe(pipefd) == -1)
		return (-1);
	ft_putstr_fd(redir->heredoc, pipefd[1]);
	ret_value = dup2(pipefd[0], 0);
	close(pipefd[0]);
	close(pipefd[1]);
	return (ret_value);
}

int	manage_stderr(t_redir *redir)
{
	int	fd;
	int	ret_value;

	fd = open(redir->pathfile, O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		return (-1);
	ret_value = dup2(fd, 2);
	close(fd);
	return (ret_value);
}
