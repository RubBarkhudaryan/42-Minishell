/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:40:29 by apatvaka          #+#    #+#             */
/*   Updated: 2025/09/04 19:31:37 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../../ast/ast.h"
# include "../../built_in/bulit_in.h"
# include "../../parsing_env/env_parser.h"
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_cmd	t_cmd;
typedef struct s_ast	t_ast;
typedef struct s_env	t_env;

typedef struct s_shell
{
	t_ast				*ast;
	t_env				*env;
}						t_shell;

int						get_exit_code(int status);
int						execute_pipe(t_ast *ast, t_shell *shell,
							bool last_pipe);
int						execute_node(t_shell *shell);

int						execute_ast(t_ast *ast, t_shell *shell, bool wait,
							int extra_fd);
int						exe_builtin_process(t_cmd *cmd, t_shell *shell,
							bool wait, int extra_fd);
int						execute_builtin(t_cmd *cmd, t_shell *shell);
char					**tokens_to_args(t_token *tokens);
char					*find_executable_path(t_ast *ast, t_shell *shell);
int						is_builtin(char *cmd);
int						launch_process(t_ast *ast, t_shell *shell, int extra_fd,
							bool wait);
int						apply_redirections(t_cmd *cmd, int extra_fd);

// utils
void					free_shell(t_shell *shell);
void					print_msg(char *name);
#endif
