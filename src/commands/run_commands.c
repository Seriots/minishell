/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 19:31:52 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/05 20:23:24 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "minishell.h"

int	run_commands(char **commands, t_shell *shell)
{
	char	*argv[4];
	pid_t	ppid;

	ppid = fork();
	if (ppid == 0)
	{
		printf("%s\n", commands[0]);
		argv[0] = "/bin/bash";
		argv[1] = "-c";
		argv[2] = commands[0];
		argv[3] = 0;
		execve("/bin/bash", argv, shell->env);
		exit(0);
	}
	wait(NULL);
	return (0);
}
