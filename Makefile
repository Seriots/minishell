CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -g
MAKE		= /bin/make


NAME		= minishell

LIB_NAMES	= dict \
			  tree \
			  ft_printf \
			  ft \
			  list \

LIBEXT_NAMES= readline

HEADER_NAMES= dict \
			  tree \
			  ft \
			  ft_printf \
			  list \

SRC_NAMES	= main \
			  builtins/utils/export_utils \
			  builtins/utils/cd_utils \
			  builtins/cd \
			  builtins/echo \
			  builtins/env \
			  builtins/exit \
			  builtins/export \
			  builtins/pwd \
			  builtins/unset \
			  free_cmd_line \
			  read_cmd_line/checker \
			  read_cmd_line/interpreter/interpreter_input \
			  read_cmd_line/interpreter/set_expression_heredoc \
			  read_cmd_line/lexer/lexer \
			  read_cmd_line/lexer/lexer_get_lexeme \
			  read_cmd_line/lexer/lexer_init_state \
			  read_cmd_line/lexer/lexer_set_size \
			  read_cmd_line/lexer/lexer_update_state \
			  read_cmd_line/parser/parser_and \
			  read_cmd_line/parser/parser_args \
			  read_cmd_line/parser/parser \
			  read_cmd_line/parser/parser_or \
			  read_cmd_line/parser/parser_pipe \
			  read_cmd_line/parser/utils \
			  read_cmd_line/read_cmd_line \
			  run_cmd_line/run_cmd_and \
			  run_cmd_line/run_cmd_args/run_cmd_args \
			  run_cmd_line/run_cmd_args/set_cmd_path \
			  run_cmd_line/run_cmd_args/run_builtins/run_builtin \
			  run_cmd_line/run_cmd_line \
			  run_cmd_line/run_cmd_or \
			  run_cmd_line/run_cmd_pipe/run_cmd_pipe \
			  run_cmd_line/run_cmd_pipe/run_pipeline \
			  shell/free_shell \
			  shell/init_shell \
			  shell/run_shell \
			  shell/utils/init_env_variable \
			  shell/utils/init_pwd \
			  shell/utils/init_shlvl \
			  shell/utils/init_envpath \
			  shell/utils/init_builtins \
			  signals/init_sigact \
			  signals/handle_signals \
			  input_modification/input_modification \
			  input_modification/removes_quotes \
			  input_modification/wildcards/check_part \
			  input_modification/wildcards/split_input_utils \
			  input_modification/wildcards/split_input \
			  input_modification/wildcards/wildcard \
			  input_modification/wildcards/wildcards_utils \
			  input_modification/special_char/question_mark \
			  input_modification/special_char/replace_special_args \
			  input_modification/env_arguments/env_arguments_utils \
			  input_modification/env_arguments/env_arguments \

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
LIB_OBJS	= 

LIB_FILES	= $(foreach l,$(LIB_NAMES),$(LIB_DIR)/$l/lib$l.a)

_GREY		= \033[30m
_RED		= \033[31m
_GREEN		= \033[32m
_YELLOW		= \033[33m
_BLUE		= \033[34m
_PURPLE		= \033[35m
_CYAN		= \033[36m
_WHITE		= \033[37m
_NO_COLOR	= \033[0m


.PHONY:			all clean fclean re rule_begin
.INTERMEDIATE:	start_compiling


all:			$(NAME)

clean:
	@echo "$(_GREEN)Removing objects$(_NO_COLOR)"
	rm -f $(OBJ)
	@if [ -d $(OBJ_DIR) ]; then \
		find $(OBJ_DIR) -type d | xargs rmdir -p --ignore-fail-on-non-empty; \
	fi

fclean:			clean
	rm -Rf .vscode
	@echo "\n$(_GREEN)Removing $(NAME)$(_NO_COLOR)"
	rm -f $(NAME)
	@for lib in $(LIB_NAMES); do \
		echo "\n$(_GREEN)$(LIB_DIR)/$${lib}/: make fclean$(_NO_COLOR)"; \
		$(MAKE) --no-print-directory -C $(LIB_DIR)/$${lib}/ fclean; \
	done

re:				
	$(MAKE) fclean
	$(MAKE) all

start_compiling:
	@echo "\n$(_GREEN)Start Compiling $(_NO_COLOR)"


$(NAME): $(LIB_FILES) $(OBJ)
	@echo "\n$(_BLUE)Linkage $(NAME)$(_NO_COLOR)"
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIB)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c start_compiling
	@if [ ! -d $(dir $@) ]; then \
		mkdir -p $(dir $@); \
	fi
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

%.a:
	@echo "\n$(_GREEN)$(dir $@): make$(_NO_COLOR)"
	@$(MAKE) --no-print-directory -C $(dir $@)
