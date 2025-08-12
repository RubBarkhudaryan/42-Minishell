/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulit_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:05:55 by apatvaka          #+#    #+#             */
/*   Updated: 2025/08/11 14:20:44 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BULIT_IN_H
# define BULIT_IN_H
# include "../parsing_env/env_parser.h"
# include <errno.h>
# include <stdio.h>  // can you delited this or not?
# include <unistd.h> // can you delited this or not?

int		ft_echo(char **args);
int		ft_pwd(char **args);
int		ft_cd(char **args, t_env *env);
int		ft_env(char **args, t_env *env_list);
int		print_export(t_env *env);
int		ft_export(char **args, t_env **env);
char	**env_to_export_string(t_env *head);
int		print_export(t_env *env);
int		print_helper(char *arg, char *error_msg);
#endif
