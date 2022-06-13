/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init_state.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 00:33:16 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/13 00:44:17 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	lexer_init_state(t_lexer_state *lexer, const char *input)
{
	lexer->i = 0;
	lexer->size = 0;
	return (lexer_update_state(lexer, input));
}
