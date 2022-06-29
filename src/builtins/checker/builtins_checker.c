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
	cd_checker(argc, argv, env);
	echo_checker(argc, argv, env);
	export_checker(argc, argv, env);
	unset_checker(argc, argv, env);
}