CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
MAKE		= /bin/make

HEADER_DIR	= include
LIB_DIR		= lib
SRC_DIR		= src
OBJ_DIR		= obj

HEADER_NAMES= libft
LIB_NAMES	= ft
NAME		= minishell
SRC_NAMES	= main

HEADER		= $(HEADER_NAMES:%=$(HEADER_DIR)/%.h)
INCLUDE		= -I$(HEADER_DIR)
LIB			= $(LIB_NAMES:%=-L$(LIB_DIR)/%) $(LIB_NAMES:%=-l%)
LIB_FILES	= $(foreach n,${LIB_NAMES},${LIB_DIR}/$n/lib$n.a)
OBJ			= $(SRC_NAMES:%=$(OBJ_DIR)/%.o)

all:	$(NAME)

$(NAME):	$(LIB_FILES) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIB)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(foreach n,%,$(LIB_DIR)/$n/lib$n.a):	$(LIB_DIR)/%
	$(MAKE) -C $<

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)
	@for lib in $(LIB_NAMES); do $(MAKE) -C $(LIB_DIR)/$${lib} fclean; done

re:	fclean all
