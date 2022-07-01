/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_line.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 02:06:46 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/01 04:17:07 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_CMD_LINE_H
# define RUN_CMD_LINE_H

# include "minishell.h"
# include "tree.h"

typedef int	(*t_run_cmd_node)(t_tree *, t_shell *);

int	run_cmd_and(t_tree *cmd_line, t_shell *shell);
int	run_cmd_args(t_tree *cmd_line, t_shell *shell);
int	run_cmd_line(t_tree *cmd_line, t_shell *shell);
int	run_cmd_or(t_tree *cmd_line, t_shell *shell);
int	run_cmd_pipe(t_tree *cmd_line, t_shell *shell);
int	run_pipeline(t_list *pipeline, t_shell *shell, int *pid);

#endif
