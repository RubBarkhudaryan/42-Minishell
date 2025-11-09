/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulit_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:05:55 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/09 13:52:20 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BULIT_IN_H
# define BULIT_IN_H
# include "../env/env_parser.h"
# include "../execute/execute.h"
# include <errno.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_shell	t_shell;

int						ft_echo(char **args);
int						ft_unset(char **args, t_env **env);
int						ft_pwd(t_env *env);
int						ft_cd(char **args, t_shell *shell);
int						ft_env(char **args, t_shell *shell);
int						ft_exit(char **args, t_shell *shell);
int						ft_export(char **args, t_shell *shell);
int						print_helper(char *arg, char *error_msg);
int						print_export(t_env *env);
char					**env_to_export_string(t_env *head);
int						add_or_replace_value(char *key, char *value, int flag,
							t_shell *shell);
int						is_valid_numeric_string(char *str);
int						has_valid_sign_prefix(char *str, int *i);
#endif
