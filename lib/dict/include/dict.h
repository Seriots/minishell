/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 22:28:52 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/09 01:08:17 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DICT_H
# define DICT_H

# include <stddef.h>

typedef struct s_dict
{
	void			*key;
	void			*value;
	struct s_dict	*next;
	struct s_dict	*previous;
}	t_dict;

void	dict_add_back(t_dict **dict, t_dict *new, void free_key(void *),
			void free_value(void *));
void	dict_add_front(t_dict **dict, t_dict *new, void free_key(void *),
			void free_value(void *));
void	dict_changeval(t_dict **dict, void *key, void *value,
			void free_value(void *));
void	dict_clear(t_dict *dict, void free_key(void *),
			void free_value(void *));
void	dict_delone(t_dict **dict, t_dict *elem, void free_key(void *),
			void free_value(void *));
t_dict	*dict_get_first(t_dict *dict);
t_dict	*dict_get_last(t_dict *dict);
t_dict	*dict_getelem_key(t_dict *dict, void *key);
t_dict	*dict_getelem_value(t_dict *dict, void *value);
t_dict	*dict_getelem_number(t_dict *dict, size_t n);
t_dict	*dict_new(void *key, void *value);
void	dict_print(t_dict *dict);
void	dict_print_values(t_dict *dict);
void	dict_print_keys(t_dict *dict);
size_t	dict_size(t_dict *dict);

#endif