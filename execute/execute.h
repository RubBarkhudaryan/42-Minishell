/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:40:29 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/05 21:17:45 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../ast/ast.h"
# include "../built_in/bulit_in.h"
# include "../env/env_parser.h"
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_cmd	t_cmd;
typedef struct s_ast	t_ast;
typedef struct s_env	t_env;
typedef struct s_token	t_token;
typedef struct s_shell
{
	t_token				*token_list;
	t_ast				*ast;
	t_env				*env;
	int					last_exit_code;
}						t_shell;

int						get_exit_code(int status);
int						execute_pipe(t_ast *ast, t_shell *shell,
							bool last_pipe);
int						execute_node(t_shell *shell);

int						execute_ast(t_ast *ast, t_shell *shell, bool wait,
							int extra_fd);
int						exe_builtin_process(t_ast *ast, t_shell *shell,
							bool wait, int extra_fd);
int						execute_builtin(t_ast *ast, t_shell *shell,
							int extra_fd);
char					**tokens_to_args(t_token *tokens);
char					*find_executable_path(t_ast *ast, char **env_str,
							t_shell *shell);
int						is_builtin(char *cmd);
int						launch_process(t_ast *ast, t_shell *shell, int extra_fd,
							bool wait);
int						apply_redirections(t_shell *shell, t_cmd *cmd,
							int extra_fd);
void					setup_pipe_fds(t_ast *ast, int pipefd, int type_fd);
// utils
void					free_shell(t_shell *shell, int flag_unlink_heredoc);
void					print_msg(char *name);
#endif
