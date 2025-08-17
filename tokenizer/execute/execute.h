/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:40:29 by apatvaka          #+#    #+#             */
/*   Updated: 2025/08/17 18:21:34 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../../ast/ast.h"
# include "../../parsing_env/env_parser.h"
# include <sys/wait.h>
# include <unistd.h>
typedef struct s_ast	t_ast;

int						execute_ast(t_ast *ast, t_env *env);
int						launch_process(char **args, char *exec_path,
							char **env_str);

#endif
