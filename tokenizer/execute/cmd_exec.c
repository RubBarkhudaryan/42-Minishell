/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:19:14 by apatvaka          #+#    #+#             */
/*   Updated: 2025/09/08 17:29:05 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void	print_msg(char *name)
{
	char	*msg;

	if (!name)
		perror("minishell");
	msg = ft_strjoin("minishell: ", name);
	if (!msg)
		perror("minishell");
	perror(msg);
	free(msg);
}

static int	token_len(t_token *tokens)
{
	int	len;

	len = 0;
	while (tokens)
	{
		len++;
		tokens = tokens->next;
	}
	return (len);
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
char	**tokens_to_args(t_token *tokens)
{
	t_token	*current;
	int		count;
	char	**args;
	int		i;

	count = token_len(tokens);
	args = malloc(sizeof(char *) * (count + 1));
	if (!count || !args)
		return (NULL);
	i = -1;
	current = tokens;
	args[count] = NULL;
	while (current)
	{
		args[++i] = ft_strdup(current->token);
		if (!args[i])
		{
			while (--i >= 0)
				free(args[i]);
			return (free(args), NULL);
		}
		current = current->next;
	}
	return (args);
}

int	apply_redirections(t_cmd *cmd, int extra_fd)
{
	if (cmd->in_pipeline != -1)
	{
		dup2(cmd->in_pipeline, STDIN_FILENO);
		close(cmd->in_pipeline);
	}
	if (cmd->out_pipeline != -1)
	{
		dup2(cmd->out_pipeline, STDOUT_FILENO);
		close(cmd->out_pipeline);
	}
	if (extra_fd != -1)
		close(extra_fd);
	return (0);
}

static int	handle_child_process(t_ast *ast, t_shell *shell, int extra_fd,
		char **env_str)
{
	char	*tmp;

	tmp = find_executable_path(ast, env_str, shell);
	if (!tmp)
	{
		print_msg(ast->cmd->cmd_name);
		free_split(env_str);
		free_shell(shell);
		exit(127);
	}
	free(ast->cmd->cmd_name);
	ast->cmd->cmd_name = tmp;
	apply_redirections(ast->cmd, extra_fd);
	execve(ast->cmd->cmd_name, ast->cmd->args, env_str);
	perror("execve");
	free_split(env_str);
	free_shell(shell);
	exit(126);
}

int	launch_process(t_ast *ast, t_shell *shell, int extra_fd, bool wait)
{
	pid_t	pid;
	char	**env_str;
	int		status;

	env_str = convert_envp_to_string(shell->env);
	if (!env_str)
	{
		perror("minishell");
		free_split(env_str);
		return (free_shell(shell), 1);
	}
	pid = fork();
	if (pid == -1)
		return (free_split(env_str), free_shell(shell), perror("minishell"), 1);
	if (pid == 0)
		handle_child_process(ast, shell, extra_fd, env_str);
	free_split(env_str);
	if (!wait)
		return (0);
	return (waitpid(pid, &status, 0), get_exit_code(status));
}
