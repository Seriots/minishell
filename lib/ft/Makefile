CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -g

NAME	= libft.a
SRCS	= error_base.c \
		  ft_atod.c \
		  ft_atoi.c \
		  ft_bzero.c \
		  ft_calloc.c \
		  ft_free_tab.c \
		  ft_get_empty.c \
		  ft_isalpha.c \
		  ft_isdigit.c \
		  ft_isalnum.c \
		  ft_isascii.c \
		  ft_isdouble.c \
		  ft_isint.c \
		  ft_isprint.c \
		  ft_itoa.c \
		  ft_memchr.c \
		  ft_memcmp.c \
		  ft_memcpy.c \
		  ft_memmove.c \
		  ft_memset.c \
		  ft_putchar_fd.c \
		  ft_putstr_fd.c \
		  ft_putendl_fd.c \
		  ft_putnbr_fd.c \
		  ft_split.c \
		  ft_strchr.c \
		  ft_strcmp.c \
		  ft_strdup.c \
		  ft_striteri.c \
		  ft_strjoin.c \
		  ft_strlcat.c \
		  ft_strlcpy.c \
		  ft_strlen.c \
		  ft_strmapi.c \
		  ft_strncmp.c \
		  ft_strnstr.c \
		  ft_strrchr.c \
		  ft_strtrim.c \
		  ft_substr.c \
		  ft_toupper.c \
		  ft_tolower.c \
		  ft_ultoa_base.c \
		  ft_utoa_base.c \
		  ft_arraylen.c \
\
		  ft_lstnew.c \
		  ft_lstappend.c \
		  ft_lstadd_front.c \
		  ft_lstsize.c \
		  ft_lstlast.c \
		  ft_lstadd_back.c \
		  ft_lstdelone.c \
		  ft_lstclear.c \
		  ft_lstiter.c \
		  ft_lstmap.c \
\
		  ft_treeaddback_left.c \
		  ft_treeaddback_right.c \
		  ft_treeaddfront_left.c \
		  ft_treeaddfront_right.c \
		  ft_treeaddtreeback_left.c \
		  ft_treeaddtreeback_right.c \
		  ft_treeclear.c \
		  ft_treedepth.c \
		  ft_treeiter_infix.c \
		  ft_treeiter_prefix.c \
		  ft_treeiter_suffix.c \
		  ft_treejoin.c \
		  ft_treelast_left.c \
		  ft_treelast_right.c \
		  ft_treeleafnew.c \
		  ft_treesize.c \
\
		  get_next_line.c \
		  get_next_line_utils.c \
\
		  ft_printf/ft_printf.c \
		  ft_printf/ft_printf_utils.c \
		  ft_printf/ft_printf_utils2.c \
		  ft_printf/ft_printf_components.c \
		  ft_printf/conversions_files/ft_putstr.c \
		  ft_printf/conversions_files/ft_putnbr.c \
		  ft_printf/conversions_files/ft_putchar.c \
		  ft_printf/conversions_files/ft_puthexa_min.c \
		  ft_printf/conversions_files/ft_putpointeur.c \
		  ft_printf/conversions_files/ft_putpointeur2.c \
		  ft_printf/conversions_files/ft_puthexa_maj.c \
		  ft_printf/conversions_files/ft_putnbr_unsigned.c \
\
		  ft_dictnew.c \
		  ft_dictadd_front.c \
		  ft_dictadd_back.c \
		  ft_dictprint.c \
		  ft_dictprint_values.c \
		  ft_dictprint_keys.c \
		  ft_dictsize.c \
		  ft_dictgetfirst.c \
		  ft_dictgetlast.c \
		  ft_dictdelone.c \
		  ft_dictgetelem_key.c \
		  ft_dictgetelem_value.c \
		  ft_dictgetelem_number.c \
		  ft_dictchangeval.c \
		  ft_dictclear.c

OBJS	= ${SRCS:%.c=%.o}

all: ${NAME}

${NAME}: ${OBJS}
	ar rc $@ $^

%.o: %.c
	${CC} ${CFLAGS} -o $@ -c $^

clean:
	rm -f ${OBJS} ${OBJS_BONUS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY : all clean fclean re
