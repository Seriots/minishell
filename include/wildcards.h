/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:08:41 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/09 22:14:03 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARDS_H
# define WILDCARDS_H

# include "list.h"

typedef struct s_wildstr
{
	char	**split;
	int		check_first;
	int		check_last;
}			t_wildstr;

/*split_input_utils.c*/
void		skip_quote_putwords(const char *s,
				int *position, char *quote);
void		skip_quote_letters(char quote, const char *s,
				int *i, int *count);
void		skip_quote_words(const char *s, int *i);

/*split_input.c*/
int			ft_split_w(char *str, t_wildstr *wildstr);

/*is_addable.c*/
int			is_addable(char *d_name, t_wildstr *split);

/*wildcards_utils.c*/
t_wildstr	*init_wildstr(char *str, t_wildstr *wildstr);
char		**list_to_array(t_list *result);
void		insert_wildcard_add(t_list **next, t_list **current,
				t_list **new, t_list **pre);

/*wildcards.c*/
char		**replace_args(char **argv);

#endif
