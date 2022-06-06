CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -g
MAKE		= /bin/make

HEADER_NAMES= libft
LIB_NAMES	= ft
NAME		= minishell
SRC_NAMES	= commands/free_commands \
			  commands/get_commands \
			  commands/run_commands \
			  main \
			  shell/free_shell \
			  shell/init_shell \
			  shell/run_shell \
			  signals/init_sigact \
			  signals/handle_signals
HEADER_DIR	= include
LIB_DIR		= lib
SRC_DIR		= src
OBJ_DIR		= obj

HEADER		= $(HEADER_NAMES:%=$(HEADER_DIR)/%.h)
INCLUDE		= -I$(HEADER_DIR)
LIB			= -lreadline $(LIB_NAMES:%=-L$(LIB_DIR)/%) $(LIB_NAMES:%=-l%)
LIB_DIRS	= $(foreach n,$(LIB_NAMES),$(LIB_DIR)/$n)
LIB_FILES	= $(foreach n,$(LIB_NAMES),$(LIB_DIR)/$n/lib$n.a)
OBJ			= $(SRC_NAMES:%=$(OBJ_DIR)/%.o)

all:	$(NAME)

$(NAME):	$(LIB_FILES) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIB)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(LIB_FILES):
	@for lib_dir in $(LIB_DIRS); do $(MAKE) -C $${lib_dir}; done

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)
	@for lib in $(LIB_NAMES); do $(MAKE) -C $(LIB_DIR)/$${lib} fclean; done

re:	fclean all
