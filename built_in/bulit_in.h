/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulit_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:05:55 by apatvaka          #+#    #+#             */
/*   Updated: 2025/09/22 15:16:48 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BULIT_IN_H
# define BULIT_IN_H
# include "../parsing_env/env_parser.h"
# include "../tokenizer/execute/execute.h"
# include <errno.h>
# include <stdio.h>  // can you delited this or not?
# include <unistd.h> // can you delited this or not?

typedef struct s_shell	t_shell;

int						ft_echo(char **args);
int						ft_unset(char **args, t_env **env);
int						ft_pwd(t_env *env);
int						ft_cd(char **args, t_shell *shell);
int						ft_env(char **args, t_shell *shell);
int						ft_export(char **args, t_shell *shell);
char					**env_to_export_string(t_env *head);
int						print_helper(char *arg, char *error_msg);
int						print_export(t_env *env);
#endif
