#include "../../../include/libft.h"
#include "../../../include/get_next_line.h"
#include "../../../include/minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int	main(int argc, char *argv[], char **env)
{
	char	**args;
	char	*command;
	int		check_error;
	int		fd;

	fd = open("src/builtins/checker/echo_test.txt", O_RDONLY);
	command = get_next_line(fd);
	if (command[ft_strlen(command) - 1] == '\n')
		command[ft_strlen(command) - 1] = 0;
	printf("----'%s'----\n", command);
	args = ft_split(command, ' ');
	while (args)
	{
		check_error = echo_command(0, args);
		if (check_error == ft_atoi(get_next_line(fd)))
			printf("Return OK\n");
		else
			printf("Return KO\n");
		free (command);
		ft_free_tab(args);
		command = get_next_line(fd);
		if (command && command[ft_strlen(command) - 1] == '\n')
			command[ft_strlen(command) - 1] = 0;
		printf("----'%s'----\n", command);
		args = ft_split(command, ' ');
	}
}
