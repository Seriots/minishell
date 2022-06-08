/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 20:33:36 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/08 22:51:06 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_tree
{
	void			*content;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_dict
{
	void			*key;
	void			*value;
	struct s_dict	*next;
	struct s_dict	*previous;
}	t_dict;

# include <stdarg.h>
# define BASE_HEXA_MIN "0123456789abcdef"
# define BASE_HEXA_MAJ "0123456789ABCDEF"
# define FLAG_BASE "0 +-#"
# define ATTRIBUT_BASE "cspdiuxX%"

typedef struct s_arg
{
	int		f_zero;
	int		f_space;
	int		f_plus;
	int		f_minus;
	int		f_hashtag;
	int		min_champs;
	int		precision;
	int		precision_detected;
	char	attribut;
}			t_arg;

/*ft_printf*/
int		ft_printf(const char *s, ...);

/*ft_printf_components*/
int		ft_check_parse(t_arg element, va_list ap, int *i, const char *s);
int		ft_printfwork(va_list ap, const char *s);
t_arg	ft_parse(const char *s, int *position);
int		ft_printf_args(t_arg element, va_list ap);

/*ft_printf_utils*/
int		ft_is_base(char c, char *base);
t_arg	ft_convert_flags(int flags[5], t_arg elem0);
void	ft_setzero(int flags[5]);
int		ft_abs(int n);
void	ft_init(t_arg *elem);

/*ft_printf_utils2.h*/
int		ft_print_minchamps(t_arg elem);
int		ft_print_precision(t_arg elem);

int		error_base(char *base);
double	ft_atod(const char *str);
int		ft_atoi(const char *nptr);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
//void	ft_free_tab(char **tab);
char	*ft_get_empty(void);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isdouble(const char *str);
int		ft_isint(const char *str);
int		ft_isprint(int c);
char	*ft_itoa(int n);

int		ft_lstappend(t_list **lst, void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);

void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);
size_t	ft_arraylen(char **array);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);

int		ft_treeaddback_left(t_tree **tree, void *content);
int		ft_treeaddback_right(t_tree **tree, void *content);
int		ft_treeaddfront_left(t_tree **tree, void *node, void *content);
int		ft_treeaddfront_right(t_tree **tree, void *node, void *content);
int		ft_treeaddfront_right(t_tree **tree, void *node, void *content);
int		ft_treeaddtreeback_left(t_tree **tree, t_tree *tree_backleft);
int		ft_treeaddtreeback_right(t_tree **tree, t_tree *tree_backright);
void	ft_treeclear(t_tree *tree, void (*del_node)(void *),
			void (*del_leaf)(void *));
int	ft_treedepth(t_tree *tree);
void	ft_treeiter_infix(t_tree *tree, void (*f_node)(void *),
			void (*f_leaf)(void *));
void	ft_treeiter_prefix(t_tree *tree, void (*f_node)(void *),
			void (*f_leaf)(void *));
void	ft_treeiter_suffix(t_tree *tree, void (*f_node)(void *),
			void (*f_leaf)(void *));
t_tree	*ft_treejoin(t_tree *tree_left, void *node, t_tree *tree_right);
t_tree	*ft_treelast_left(t_tree *tree);
t_tree	*ft_treelast_right(t_tree *tree);
t_tree	*ft_treeleafnew(void *leaf);
int		ft_treesize(t_tree *tree);

int		ft_tolower(int c);
int		ft_toupper(int c);
char	*ft_ultoa_base(unsigned long int nbr, char *base);
char	*ft_utoa_base(unsigned int nbr, char *base);

/*
//	GET_NEXT_LINE
*/
char	*get_next_line(int fd);
int		update_line(char **line, char *buff, int *read_size, unsigned int *i_b);
char	*str_buff_join(char *str, char *mem, size_t size);

/*
* DICT
*/
t_dict	*ft_dictnew(char *key, char *value);
void	ft_dictadd_front(t_dict **dict, t_dict *new, void free_key(void *), void free_value(void *));
void	ft_dictprint(t_dict *dict, char *str);
void	ft_dictprint_values(t_dict *dict);
void	ft_dictprint_keys(t_dict *dict);
void	ft_dictdelone(t_dict **dict, t_dict *elem, void free_key(void *), void free_value(void *));
void	ft_dictclear(t_dict *dict, void free_key(void *), void free_value(void *));
size_t	ft_dictsize(t_dict *dict);
t_dict	*ft_dictget_first(t_dict *dict);
t_dict	*ft_dictget_last(t_dict *dict);
void	ft_dictadd_back(t_dict **dict, t_dict *new, void free_key(void *), void free_value(void *));
t_dict	*ft_dictgetelem_key(t_dict *dict, void *key);
t_dict	*ft_dictgetelem_value(t_dict *dict, void *value);
t_dict	*ft_dictgetelem_number(t_dict *dict, size_t n);
void	ft_dictchangeval(t_dict **dict, void *key, void *value, void free_value(void *));
#endif
