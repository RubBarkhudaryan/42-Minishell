/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:34:37 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/05 18:34:37 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "execute.h"

int	is_dollar(char *tmp)
{
	int i;

	i = -1;
	while (tmp[++i])
		if (tmp[i] == '$')
			return (1);
	return (0);
}

void	shlvl_exec(t_shell *shell)
{
	short	shlvl;
	char	*level;
	char	*tmp;

	level = get_value_from_env(shell->env, "SHLVL");
	if (!level)
	{
		add_or_replace_value("SHLVL", "1", 0, shell);
		return ;
	}
	shlvl = ft_atoi(level);
	tmp = ft_itoa(shlvl + 1);
	if (!tmp)
		return (perror("malloc failed\n"), (void)0);
	add_or_replace_value(ft_strdup("SHLVL"), ft_strdup(tmp), 0, shell);
	free(tmp);
}

void	update_env_var(t_ast *ast, t_shell *shell)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;

	while (ast->cmd && ast->cmd->args && ast->cmd->args[++i])
		tmp = ast->cmd->args[i];
	if (!tmp)
		return ;
	add_or_replace_value(ft_strdup("_"), ft_strdup(tmp), 0, shell);
}

int	execute_command(t_ast *ast, t_shell *shell, bool wait, int extra_fd)
{
	int		i;
	int		status;
	char	*temp;

	i = -1;
	while (ast->cmd->args && ast->cmd->args[++i])
	{
		if (is_dollar(ast->cmd->args[i]))
		{
			temp = expand_dollar_token(ast->cmd->args[i], shell);
			free(ast->cmd->args[i]);
			ast->cmd->args[i] = temp;
		}
	}
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
	return (waitpid(pid, &status, 0), get_exit_code(status));
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
