/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:40:25 by apatvaka          #+#    #+#             */
/*   Updated: 2025/10/02 20:04:58 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int is_dollar(char *tmp)
{
	int i;

	i = -1;
	while(tmp[++i])
		if(tmp[i] == '$')
			return (1);
	return (0);
}

int	execute_command(t_ast *ast, t_shell *shell, bool wait, int extra_fd)
{
	int		i;
	int		status;
	char	*temp;

	i = -1;
	while (ast->cmd->args[++i])
		if(is_dollar(ast->cmd->args[i]))
		{
			temp = expand_dollar_token(ast->cmd->args[i], shell);
			free(ast->cmd->args[i]);
			ast->cmd->args[i] = temp;
		}
	if (is_builtin(ast->cmd->cmd_name) && ast->cmd->out_pipeline == -1
		&& ast->cmd->in_pipeline == -1)
		return (execute_builtin(ast->cmd, shell));
	else if (is_builtin(ast->cmd->cmd_name))
		return (exe_builtin_process(ast->cmd, shell, wait, extra_fd));
	status = launch_process(ast, shell, extra_fd, wait);
	return (status);
}

int	execute_subshell(t_ast *ast, t_shell *shell, bool wait, int extra_fd)
{
	pid_t	pid;
	int		exit_code;
	int		status;

	pid = fork();
	if (pid == -1)
		return (free_shell(shell, 0), perror("minishell"), 1);
	if (pid == 0)
	{
		exit_code = execute_ast(ast->left, shell, wait, extra_fd);
		if (extra_fd != -1)
			close(extra_fd);
		free_shell(shell, 0);
		exit(exit_code);
	}
	if (!wait)
		return (0);
	return (waitpid(pid, &status, 0), get_exit_code(status));
}

int	execute_ast(t_ast *ast, t_shell *shell, bool wait, int extra_fd)
{
	int	exit_code;

	if (!ast)
		return (1);
	if (ast->type == NODE_SUBSHELL)
		return (execute_subshell(ast, shell, wait, extra_fd));
	else if (ast->type == NODE_AND)
	{
		exit_code = execute_ast(ast->left, shell, wait, extra_fd);
		if (exit_code == 0)
			return (execute_ast(ast->right, shell, wait, extra_fd));
		return (exit_code);
	}
	else if (ast->type == NODE_OR)
	{
		exit_code = execute_ast(ast->left, shell, wait, extra_fd);
		if (exit_code != 0)
			return (execute_ast(ast->right, shell, wait, extra_fd));
		return (exit_code);
	}
	else if (ast->type == NODE_PIPE)
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
