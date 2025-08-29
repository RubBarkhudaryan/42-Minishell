/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:40:29 by apatvaka          #+#    #+#             */
/*   Updated: 2025/08/29 23:42:00 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../../ast/ast.h"
# include "../../built_in/bulit_in.h"
# include "../../parsing_env/env_parser.h"
# include <stdbool.h>
# include <sys/wait.h>
# include <unistd.h>

#define XCLOSE(fd) do { \
    printf("Closing fd %d at %s:%d\n", fd, __FILE__, __LINE__); \
    if(close(fd)<0)printf("fd is closed\n\n"); \
} while (0)

typedef struct s_cmd	t_cmd;
typedef struct s_ast	t_ast;

int						get_exit_code(int status);

int						execute_ast(t_ast *ast, t_env *env, bool wait,
							int extra_fd);
int						execute_node(t_ast *ast, t_env *env);
char					**tokens_to_args(t_token *tokens);
char					*find_executable_path(t_cmd *cmd, char *path);
int						is_builtin(char *cmd);
int						execute_builtin(t_cmd *cmd, t_env *env);
int						launch_process(t_cmd *cmd, char **env_str, int extra_fd,
							bool wait);
int						apply_redirections(t_cmd *cmd, int extra_fd);
#endif
