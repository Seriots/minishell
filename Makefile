CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -g
MAKE		= /bin/make

HEADER_NAMES= libft
LIB_NAMES	= ft
NAME		= minishell
SRC_NAMES	= commands/free_command \
			  commands/free_commands \
			  commands/get_command/get_bzero_command \
			  commands/get_command/get_command \
			  commands/get_command/set_arguments \
			  commands/get_command/set_redirections \
			  commands/get_command/utils/count_arguments \
			  commands/get_command/utils/count_redirections \
			  commands/get_command/utils/get_argument_after \
			  commands/get_command/utils/get_argument \
			  commands/get_command/utils/is_argument_equal_to \
			  commands/get_command/utils/is_argument_in_input \
			  commands/get_command/utils/is_argument_redirection \
			  commands/get_command/utils/skip_argument \
			  commands/get_command/utils/skip_redirection \
			  commands/get_command/utils/skip_redirections \
			  commands/get_command/utils/skip_to \
			  commands/get_command/utils/skip_to_next_argument \
			  commands/get_command/utils/skip_whitespaces \
			  commands/get_commands \
			  commands/run_commands \
			  main \
			  shell/free_shell \
			  shell/init_shell \
			  shell/run_shell \
			  signals/init_sigact \
			  signals/handle_signals \
			  commands/parse_input/contain_and \
			  commands/parse_input/contain_or \
			  commands/parse_input/contain_pipe \
			  commands/parse_input/is_between_brackets \
			  commands/parse_input/parse_input_and \
			  commands/parse_input/parse_input_brackets \
			  commands/parse_input/parse_input_or \
			  commands/parse_input/parse_input_pipe \
			  commands/parse_input/parse_input_simple \
			  commands/parse_input/parse_input \
			  commands/get_commands/get_argument \
			  commands/get_commands/get_bzero_command \
			  commands/get_commands/get_command \
			  commands/get_commands/set_arguments \
			  commands/get_commands/set_redirections \
			  commands/get_commands/utils/count_arguments \
			  commands/get_commands/utils/count_redirections \
			  commands/get_commands/utils/get_argument_after \
			  commands/get_commands/utils/is_argument_equal \
			  commands/get_commands/utils/is_argument_in_input \
			  commands/get_commands/utils/is_argument_redirection \
			  commands/get_commands/utils/skip_argument \
			  commands/get_commands/utils/skip_redirections \
			  commands/get_commands/utils/skip_to_next_argument \
			  commands/get_commands/utils/skip_whitespaces


HEADER_DIR	= include
LIB_DIR		= lib
SRC_DIR		= src
OBJ_DIR		= obj

HEADER		= $(HEADER_NAMES:%=$(HEADER_DIR)/%.h)
INCLUDE		= -I$(HEADER_DIR)
LIB			= -lreadline $(LIB_NAMES:%=-L$(LIB_DIR)/%) $(LIB_NAMES:%=-l%)
LIB_FILES	= $(foreach n,$(LIB_NAMES),$(LIB_DIR)/$n/lib$n.a)
OBJ			= $(SRC_NAMES:%=$(OBJ_DIR)/%.o)

all:	$(NAME)

$(NAME):	$(LIB_FILES) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIB)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

%.a:
	$(MAKE) -C $(dir $@)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)
	@for lib_dir in $(dir $(LIB_FILES)); do $(MAKE) -C $${lib_dir} fclean; done

re:	fclean all
