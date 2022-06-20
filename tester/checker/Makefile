CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
MAKE		= /bin/make


NAME		= tester_checker

LIB_NAMES	= ft
LIBEXT_NAMES=

HEADER_NAMES= checker \
			  read_cmd_line
SRC_NAMES	= checker/checker \
			  lexer/lexer \
			  lexer/lexer_get_lexeme \
			  lexer/lexer_init_state \
			  lexer/lexer_set_size \
			  lexer/lexer_update_state


LIB_DIR		= ../../lib

LIB			= $(LIBEXT_NAMES:%=-l%) \
			  $(LIB_NAMES:%=-L$(LIB_DIR)/%) \
			  $(LIB_NAMES:%=-l%)

HEADER_DIR	= ../../include
SRC_DIR		= ../../src/read_cmd_line
OBJ_DIR		= obj

INCLUDE		= -I$(HEADER_DIR)

HEADER		= $(HEADER_NAMES:%=$(HEADER_DIR)/%.h)
OBJ			= $(SRC_NAMES:%=$(OBJ_DIR)/%.o)

LIB_FILES	= $(foreach l,$(LIB_NAMES),$(LIB_DIR)/$l/lib$l.a)


all: $(NAME)

$(NAME):	$(LIBFILES) $(OBJ) $(OBJ_DIR)/main.o
	$(CC) $(CFLAGS) $(OBJ) $(OBJ_DIR)/main.o $(LIB) -o $@

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@if [ ! -d $(dir $@) ]; then \
		mkdir -p $(dir $@); \
	fi
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o $@

$(OBJ_DIR)/main.o: main.c
	@if [ ! -d $(dir $@) ]; then \
		mkdir -p $(dir $@); \
	fi
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o $@

%.a:
	$(MAKE) --no-print-directory -C $(dir $@)

clean:
	rm -f $(OBJ) main.o
	rm -r $(OBJ_DIR)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all main clean fclean re
