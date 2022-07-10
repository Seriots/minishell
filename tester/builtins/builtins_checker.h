/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_checker.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:20:43 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/07/09 20:21:06 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_CHECKER_H
# define BUILTINS_CHECKER_H

void	export_checker(int argc, char *argv[], char **env);
void	echo_checker(int argc, char *argv[], char **env);
void	cd_checker(int argc, char *argv[], char **env);
void	unset_checker(int argc, char *argv[], char **env);

#endif
