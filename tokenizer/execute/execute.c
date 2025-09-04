/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:40:25 by apatvaka          #+#    #+#             */
/*   Updated: 2025/09/04 19:29:07 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	execute_ast(t_ast *ast, t_shell *shell, bool wait, int extra_fd);

int	execute_command(t_ast *ast, t_shell *shell, bool wait, int extra_fd)
{
	int	status;

	if (is_builtin(ast->cmd->cmd_name) && ast->cmd->out_pipeline == -1
		&& ast->cmd->in_pipeline == -1)
		return (execute_builtin(ast->cmd, shell));
	else if (is_builtin(ast->cmd->cmd_name))
		return (exe_builtin_process(ast->cmd, shell, wait, extra_fd));
	status = launch_process(ast, shell, extra_fd, wait);
	return (status);
}

int	execute_ast(t_ast *ast, t_shell *shell, bool wait, int extra_fd)
{
	if (!ast)
		return (1);
	// if (ast->type == NODE_AND)
	// 	return (execute_ast(ast->left, env) && execute_ast(ast->right, env));
	// 		// Change this to another function to start a new process.
	// else if (ast->type == NODE_OR)
	// 	return (execute_ast(ast->left, env) || execute_ast(ast->right, env));
	// 		// Change this to another function to start a new process.
	// else
	if (ast->type == NODE_PIPE)
		return (execute_pipe(ast, shell, wait));
	else if (ast->type == NODE_COMMAND)
		return (execute_command(ast, shell, wait, extra_fd));
	return (0);
}

int	execute_node(t_shell *shell)
{
	if (!shell->ast)
		return (1);
	return (execute_ast(shell->ast, shell, true, -1));
}
