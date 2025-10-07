/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:19:14 by apatvaka          #+#    #+#             */
/*   Updated: 2025/10/07 18:54:30 by apatvaka         ###   ########.fr       */
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

int	open_fd(t_redir *redir, int redir_fd, int flags, mode_t mode)
{
	int	fd;

	fd = open(redir->filename, flags, mode);
	if (fd == -1)
		return (-1);
	if (redir->type == TK_HEREDOC)
		unlink(redir->filename);
	dup2(fd, redir_fd);
	close(fd);
	return (fd);
}

int	open_redirect_file(t_redir *redir, t_shell *shell)
{
	int	fd;

	(void)shell;
	if (redir->type == TK_REDIR_INPUT)
		return (open_fd(redir, STDIN_FILENO, O_RDONLY, 0));
	else if (redir->type == TK_REDIR_OUTPUT)
		return (open_fd(redir, STDOUT_FILENO, O_WRONLY | O_CREAT | O_TRUNC,
				0644));
	else if (redir->type == TK_APPEND)
		return (open_fd(redir, STDOUT_FILENO, O_WRONLY | O_CREAT | O_APPEND,
				0644));
	else if (redir->type == TK_HEREDOC)
	{
		fd = open_fd(redir, STDIN_FILENO, O_RDONLY, 0);
		return (fd);
	}
	else
		return (-1);
}

int	apply_redirections(t_shell *shell, t_cmd *cmd, int extra_fd)
{
	t_redir	*tmp;

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
	if (cmd->redirs_cmd)
	{
		tmp = cmd->redirs_cmd->redirs;
		while (tmp)
		{
			if (open_redirect_file(tmp, shell) == -1)
				return (print_msg(tmp->filename), EXIT_FAILURE);
			tmp = tmp->next;
		}
	}
	return (0);
}

static int	handle_child_process(t_ast *ast, t_shell *shell, int extra_fd,
		char **env_str)
{
	char	*tmp;

	tmp = find_executable_path(ast, env_str, shell);
	if (!tmp)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(ast->cmd->cmd_name, 2);
		ft_putstr_fd(": command not found\n", 2);
		free_split(env_str);
		free_shell(shell, 0);
		exit(127);
	}
	free(ast->cmd->cmd_name);
	ast->cmd->cmd_name = tmp;
	if (apply_redirections(shell, ast->cmd, extra_fd) == -1)
	{
		free_split(env_str);
		free_shell(shell, 1);
		exit(EXIT_FAILURE);
	}
	execve(ast->cmd->cmd_name, ast->cmd->args, env_str);
	perror("execve");
	free_split(env_str);
	free_shell(shell, 0);
	exit(126);
}

int	launch_process(t_ast *ast, t_shell *shell, int extra_fd, bool wait)
{
	pid_t	pid;
	char	**env_str;
	int		status;

	if (ast->cmd->redirs_cmd && !ast->cmd->cmd_name)
		return (0);
	env_str = convert_envp_to_string(shell->env);
	if (!env_str)
	{
		perror("minishell");
		free_split(env_str);
		return (free_shell(shell, 0), 1);
	}
	pid = fork();
	if (pid == -1)
		return (free_split(env_str), free_shell(shell, 1), perror("minishell"),
			1);
	if (pid == 0)
		handle_child_process(ast, shell, extra_fd, env_str);
	free_split(env_str);
	if (!wait)
		return (0);
	return (waitpid(pid, &status, 0), get_exit_code(status));
}
