/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 02:16:00 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/09 20:33:48 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "read_cmd_line.h"

# define FORBIDDEN_INIT 60// (4 + 8 + 16 + 32)

# define ALLOWED_NEWLINE 0
# define ALLOWED_PAR_LEFT 0
# define ALLOWED_PAR_RIGHT 57 // (1 + 8 + 16 + 32)
# define ALLOWED_OR 2050 // (2 + 2048)
# define ALLOWED_AND 2050 // (2 + 2048)
# define ALLOWED_PIPE 2050 // (2 + 2048)
# define ALLOWED_RED_HEREDOC 61 // (1 + 4 + 8 + 16 + 32)
# define ALLOWED_RED_STDIN 61 // (1 + 4 + 8 + 16 + 32)
# define ALLOWED_RED_APPEND_STDOUT 61 // (1 + 4 + 8 + 16 + 32)
# define ALLOWED_RED_STDOUT 61 // (1 + 4 + 8 + 16 + 32)
# define ALLOWED_RED_STDERR 61 // (1 + 4 + 8 + 16 + 32)
# define ALLOWED_ARGUMENT 61 // (1 + 4 + 8 + 16 + 32)

# define FORBIDDEN_NEWLINE 4095 // (4096 - 1)
# define FORBIDDEN_PAR_LEFT 61 // (1 + 4 + 8 + 16 + 32)
# define FORBIDDEN_PAR_RIGHT 4034 // (2 + 64 + 128 + 256 + 512 + 1024 + 2048)
# define FORBIDDEN_OR 61 // (1 + 4 + 8 + 16 + 32)
# define FORBIDDEN_AND 61 // (1 + 4 + 8 + 16 + 32)
# define FORBIDDEN_PIPE 61 // (1 + 4 + 8 + 16 + 32)
# define FORBIDDEN_RED_HEREDOC 2
# define FORBIDDEN_RED_STDIN 2
# define FORBIDDEN_RED_APPEND_STDOUT 2
# define FORBIDDEN_RED_STDOUT 2
# define FORBIDDEN_RED_STDERR 2
# define FORBIDDEN_ARGUMENT 2

int	checker(t_token *tokens, const char *input);

#endif
