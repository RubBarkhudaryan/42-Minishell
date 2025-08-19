/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:40:29 by apatvaka          #+#    #+#             */
/*   Updated: 2025/08/18 15:19:44 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../../ast/ast.h"
# include "../../parsing_env/env_parser.h"
# include <sys/wait.h>
# include <unistd.h>
typedef struct s_ast	t_ast;

int						launch_process(char **args, char *exec_path,
							char **env_str);
int						execute_ast(t_ast *ast, t_env *env);
char					**tokens_to_args(t_token *tokens);
char					*find_executable_path(t_token *cmd, char *path);
int						is_builtin(char *cmd);
int						execute_builtin(char *cmd, char **args, t_env *env);
#endif
