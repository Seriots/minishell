CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
MAKE		= /bin/make


NAME		= tester_lexer

LIB_NAMES	= ft
LIBEXT_NAMES=

HEADER_NAMES= lexer \
			  read_cmd_line
SRC_NAMES	= lexer \
			  lexer_get_lexeme \
			  lexer_init_state \
			  lexer_set_size \
			  lexer_update_state


LIB_DIR		= ../../lib

LIB			= $(LIBEXT_NAMES:%=-l%) \
			  $(LIB_NAMES:%=-L$(LIB_DIR)/%) \
			  $(LIB_NAMES:%=-l%)

HEADER_DIR	= ../../include
SRC_DIR		= ../../src/read_cmd_line/lexer

INCLUDE		= -I$(HEADER_DIR)

HEADER		= $(HEADER_NAMES:%=$(HEADER_DIR)/%.h)
OBJ			= $(SRC_NAMES:%=%.o)

LIB_FILES	= $(foreach l,$(LIB_NAMES),$(LIB_DIR)/$l/lib$l.a)


all: $(NAME)

$(NAME):	$(LIBFILES) $(OBJ) main
	$(CC) $(CFLAGS) $(OBJ) main.o $(LIB) -o $@

%.o:	$(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o $@

main:
	$(CC) $(CFLAGS) $(INCLUDE) -c main.c -o main.o

%.a:
	$(MAKE) --no-print-directory -C $(dir $@)

clean:
	rm -f $(OBJ) main.o

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all main clean fclean re
