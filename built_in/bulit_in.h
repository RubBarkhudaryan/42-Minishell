/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulit_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:05:55 by apatvaka          #+#    #+#             */
/*   Updated: 2025/07/23 17:07:04 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BULIT_IN_H
# define BULIT_IN_H
# include "../parsing_env/env_parser.h"
# include <stdio.h>  // can you delited this or not?
# include <unistd.h> // can you delited this or not?

int	ft_echo(char **args);
int	ft_pwd(char **args); //??
int	ft_cd(char **args, t_env *env);
int	args_len(char **args);
#endif
