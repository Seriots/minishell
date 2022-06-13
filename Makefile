CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
MAKE		= /bin/make


NAME		= minishell

LIB_NAMES	= dict \
			  ft_printf \
			  ft \
			  list \
			  tree
LIBEXT_NAMES= readline

HEADER_NAMES= dict \
			  ft \
			  ft_printf \
			  list \
			  tree
SRC_NAMES	= main \
			  shell/free_shell \
			  shell/init_shell \
			  shell/run_shell \
			  shell/utils/init_env_variable \
			  signals/init_sigact \
			  signals/handle_signals \
			  commands/free_command \
			  commands/free_commands \
			  commands/get_commands/get_bzero_command \
			  commands/get_commands/get_command \
			  commands/get_commands/get_commands \
			  commands/get_commands/parse_input \
			  commands/get_commands/parse_input_and \
			  commands/get_commands/parse_input_brackets \
			  commands/get_commands/parse_input_or \
			  commands/get_commands/parse_input_pipe \
			  commands/get_commands/parse_input_simple \
			  commands/get_commands/set_arguments \
			  commands/get_commands/set_redirections \
			  commands/get_commands/utils/count_arguments \
			  commands/get_commands/utils/count_redirections \
			  commands/get_commands/utils/get_argument_after \
			  commands/get_commands/utils/get_argument \
			  commands/get_commands/utils/is_argument_equal_to \
			  commands/get_commands/utils/is_argument_in_input \
			  commands/get_commands/utils/is_argument_sep \
			  commands/get_commands/utils/is_between_brackets \
			  commands/get_commands/utils/is_sep_equal_to \
			  commands/get_commands/utils/skip_argument \
			  commands/get_commands/utils/skip_redirections \
			  commands/get_commands/utils/skip_sep \
			  commands/get_commands/utils/skip_to \
			  commands/get_commands/utils/skip_to_next_argument \
			  commands/get_commands/utils/skip_whitespaces \
			  commands/run_commands/fork_and_run_sub_commands \
			  commands/run_commands/run_command \
			  commands/run_commands/run_commands \
			  commands/run_commands/run_pipe_commands \
			  commands/run_commands/run_tree_commands \
			  commands/run_commands/set_heredocs


LIB_DIR		= lib

LIB			= $(LIBEXT_NAMES:%=-l%) \
			  $(LIB_NAMES:%=-L$(LIB_DIR)/%) \
			  $(LIB_NAMES:%=-l%)

HEADER_DIR	= include
SRC_DIR		= src
OBJ_DIR		= obj

INCLUDE		= -I$(HEADER_DIR)

HEADER		= $(HEADER_NAMES:%=$(HEADER_DIR)/%.h)
OBJ			= $(SRC_NAMES:%=$(OBJ_DIR)/%.o)

LIB_FILES	= $(foreach l,$(LIB_NAMES),$(LIB_DIR)/$l/lib$l.a)

GREEN		= \033[0;32m
NO_COLOR	= \033[0m


all:			$(NAME)

clean:
	@echo "$(GREEN)Removing objects$(NO_COLOR)"
	rm -f $(OBJ)
	@if [ -d $(OBJ_DIR) ]; then \
		find $(OBJ_DIR) -type d | xargs rmdir -p --ignore-fail-on-non-empty; \
	fi

fclean:			clean
	rm -Rf .vscode
	@echo "\n$(GREEN)Removing $(NAME)$(NO_COLOR)"
	rm -f $(NAME)
	@for lib in $(LIB_NAMES); do \
		echo "\n$(GREEN)$(LIB_DIR)/$${lib}/: make fclean$(NO_COLOR)"; \
		$(MAKE) --no-print-directory -C $(LIB_DIR)/$${lib}/ fclean; \
	done

re:				
	$(MAKE) fclean
	$(MAKE) all


$(NAME): $(LIB_FILES) $(OBJ)
	@echo "\n$(GREEN)Linkage $(NAME)$(NO_COLOR)"
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIB)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c | echo_compiling
	@if [ ! -d $(dir $@) ]; then \
		mkdir -p $(dir $@); \
	fi
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

echo_compiling:
	@echo "\n$(GREEN)Compiling objects$(NO_COLOR)"

%.a:
	@echo "\n$(GREEN)$(dir $@): make$(NO_COLOR)"
	@$(MAKE) --no-print-directory -C $(dir $@)


.PHONY:			all clean echo_compiling fclean re
