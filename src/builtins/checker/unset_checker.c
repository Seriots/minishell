#include "../../../include/libft.h"
#include "../../../include/get_next_line.h"
#include "../../../include/minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int	dict_compare_unset(t_dict	*dict_avant, t_dict *dict_now)
{
	t_dict	*copy_avant;
	t_dict	*copy_now;
	int		found;

	copy_now = dict_now;
	while (copy_now)
	{
		found = 0;
		copy_avant = dict_avant;
		while (copy_avant)
		{
			//printf("je compare tu declare=%s %s %s %s\n", (char *)copy_avant->value, (char *)copy_now->value, (char *)copy_avant->key, (char *)copy_now->key);
			if (!ft_strncmp(copy_avant->value, copy_now->value, ft_strlen(copy_avant->value) + 1) && !ft_strncmp(copy_avant->key, copy_now->key, ft_strlen(copy_avant->key) + 1))
				found = 1;
			copy_avant = copy_avant->next;
		}
		if (found == 0)
			printf("<%s=%s\n", (char *)copy_now->key, (char *)copy_now->value);
		copy_now = copy_now->next;
	}
	copy_now = dict_now;
	copy_avant = dict_avant;
	while (copy_avant)
	{
		found = 0;
		copy_now = dict_now;
		while (copy_now)
		{
			//printf("je compare tu declare=%s %s %s %s\n", (char *)copy_now->value, (char *)copy_avant->value, (char *)copy_now->key, (char *)copy_avant->key);
			if (!ft_strncmp(copy_now->value, copy_avant->value, ft_strlen(copy_now->value) + 1) && !ft_strncmp(copy_now->key, copy_avant->key, ft_strlen(copy_now->key) + 1))
				found = 1;
			copy_now = copy_now->next;
		}
		if (found == 0)
			printf("<%s=%s\n", (char *)copy_avant->key, (char *)copy_avant->value);
		copy_avant = copy_avant->next;
	}
	return (1);
}

void	unset_checker(int argc, char *argv[], char **env)
{
	char	**args;
	char	*command;
	char	*check_error;
	t_shell	shell;
	t_dict	*env_avant;
	t_dict	*export_avant;
	int		fd;

	printf("----------------UNSET----------------\n");
	init_shell(&shell, env);
	fd = open("src/builtins/checker/unset_test.txt", O_RDONLY);
	command = get_next_line(fd);
	if (command[ft_strlen(command) - 1] == '\n')
		command[ft_strlen(command) - 1] = 0;
	printf("----'%s'----\n", command);
	args = ft_split(command, ' ');
	while (args)
	{
		env_avant = dict_copy(shell.env);
		export_avant = dict_copy(shell.export);
		check_error = get_next_line(fd);
		if (unset_command(&shell, args) == ft_atoi(check_error))
			printf("Return OK\n");
		else
			printf("Return KO\n");
		printf("diff env:\n");
		dict_compare_unset(env_avant, shell.env);
		printf("diff export:\n");
		dict_compare_unset(export_avant, shell.export);
		free (command);
		free(check_error);
		ft_free_tab(args);
		dict_clear(env_avant, free, free);
		dict_clear(export_avant, free, free);
		command = get_next_line(fd);
		if (command && command[ft_strlen(command) - 1] == '\n')
			command[ft_strlen(command) - 1] = 0;
		printf("----'%s'----\n", command);
		args = ft_split(command, ' ');
	}
	free_shell(&shell);
}
