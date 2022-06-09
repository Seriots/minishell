CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
MAKE		= /bin/make


NAME		= minishell

LIB_NAMES	= dict \
			  ft \
			  ft_printf \
			  list \
			  tree
LIBEXT_NAMES= 

HEADER_NAMES= dict \
			  ft \
			  ft_printf \
			  list \
			  tree
SRC_NAMES	= main \
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
