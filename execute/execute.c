/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 13:44:33 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/09 13:44:33 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	expand_command_variables(t_ast *ast, t_shell *shell)
{
	int		i;
	char	*temp;
	char	*res;

	i = -1;
	temp = expand_dollar_token(ast->cmd->cmd_name, shell, 0);
	res = expand_nested_quote(temp, has_heredoc(ast->cmd));
	free(ast->cmd->cmd_name);
	ast->cmd->cmd_name = ft_strdup(res);
	free(temp);
	free(res);
	while (ast->cmd->args && ast->cmd->args[++i])
	{
		if (is_dollar(ast->cmd->args[i]))
		{
			temp = expand_dollar_token(ast->cmd->args[i], shell, 0);
			res = expand_nested_quote(temp, has_heredoc(ast->cmd));
			free(ast->cmd->args[i]);
			free(temp);
			ast->cmd->args[i] = temp;
		}
	}
}

int	execute_command(t_ast *ast, t_shell *shell, bool wait, int extra_fd)
{
	int	status;

	expand_command_variables(ast, shell);
	update_env_var(ast, shell);
	if (ast->cmd->cmd_name && ft_strcmp(ast->cmd->cmd_name,
			"./minishell") == 0)
		shlvl_exec(shell);
	if (is_builtin(ast->cmd->cmd_name) && ast->cmd->out_pipeline == -1
		&& ast->cmd->in_pipeline == -1)
		return (execute_builtin(ast, shell, extra_fd));
	else if (is_builtin(ast->cmd->cmd_name))
		return (exe_builtin_process(ast, shell, wait, extra_fd));
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
		apply_redirections(shell, ast->cmd, extra_fd);
		exit_code = execute_ast(ast->left, shell, wait, -1);
		if (extra_fd != -1)
			close(extra_fd);
		if (ast->cmd->in_pipeline != -1)
			close(ast->cmd->in_pipeline);
		if (ast->cmd->out_pipeline != -1)
			close(ast->cmd->out_pipeline);
		free_shell(shell, 0);
		exit(exit_code);
	}
	if (!wait)
		return (0);
	waitpid(pid, &status, 0);
	return (get_exit_code(status));
}

int	execute_ast(t_ast *ast, t_shell *shell, bool wait, int extra_fd)
{
	int	exit_code;

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
		return (execute_pipe(ast, shell, true));
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
