/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 02:16:00 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/20 22:54:57 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "read_cmd_line.h"

# define FORBIDDEN_INIT (4 + 8 + 16 + 32)

# define ALLOWED_NEWLINE 0
# define ALLOWED_PAR_LEFT 0
# define ALLOWED_PAR_RIGHT (1 + 8 + 16 + 32)
# define ALLOWED_OR (2 + 2048)
# define ALLOWED_AND (2 + 2048)
# define ALLOWED_PIPE (2 + 2048)
# define ALLOWED_RED_HEREDOC (1 + 4 + 8 + 16 + 32)
# define ALLOWED_RED_STDIN (1 + 4 + 8 + 16 + 32)
# define ALLOWED_RED_APPEND_STDOUT (1 + 4 + 8 + 16 + 32)
# define ALLOWED_RED_STDOUT (1 + 4 + 8 + 16 + 32)
# define ALLOWED_RED_STDERR (1 + 4 + 8 + 16 + 32)
# define ALLOWED_ARGUMENT (1 + 4 + 8 + 16 + 32)

# define FORBIDDEN_NEWLINE (4096 - 1)
# define FORBIDDEN_PAR_LEFT (1 + 4 + 8 + 16 + 32)
# define FORBIDDEN_PAR_RIGHT (2 + 2048)
# define FORBIDDEN_OR (1 + 4 + 8 + 16 + 32)
# define FORBIDDEN_AND (1 + 4 + 8 + 16 + 32)
# define FORBIDDEN_PIPE (1 + 4 + 8 + 16 + 32)
# define FORBIDDEN_RED_HEREDOC 2
# define FORBIDDEN_RED_STDIN 2
# define FORBIDDEN_RED_APPEND_STDOUT 2
# define FORBIDDEN_RED_STDOUT 2
# define FORBIDDEN_RED_STDERR 2
# define FORBIDDEN_ARGUMENT 2

int	checker(t_token *tokens, const char *input);

#endif
