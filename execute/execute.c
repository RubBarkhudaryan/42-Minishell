/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/11/09 13:44:33 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/09 13:44:33 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"


// int	quotes_count(char *token)
// {
// 	int i;
// 	int count;
// 	int in_quote;

// 	i = 0;
// 	count = 0;
// 	in_quote = 0;
// 	while (token[i])
// 	{
// 		if (token[i] == '\'' || token[i] == '\"')
// 		{
// 			if (in_quote == 0)
// 			{
// 				in_quote = token[i];
// 				count++;
// 			}
// 			else if (in_quote == token[i])
// 				in_quote = 0;
// 		}
// 		i++;
// 	}
// 	return (count);
// }

// char	**split_by_quotes(char *token)
// {
// 	char **arr;
// 	char in_quote;
// 	int k;
// 	int i;
// 	int j;

// 	arr = malloc(sizeof(char *) * (quotes_count(token) + 1));
// 	if (!arr)
// 		return (NULL);
// 	i = 0;
// 	k = 0;
// 	in_quote = ' ';
// 	while (token[i])
// 	{
// 		j = 0;
// 		if (ft_inset(token[i + j], "\'\""))
// 		{
// 			in_quote = token[i + j];
// 			++j;
// 			while (token[i + j] && token[i + j] != in_quote)
// 				++j;
// 			in_quote = ' ';
// 		}
// 		else
// 		{
// 			while (token[i + j] && !ft_inset(token[i + j], "\'\""))
// 				++j;
// 		}
// 		arr[k] = ft_substr(token, i, j);
// 		++k;
// 		i += j;
// 	}
// 	arr[k] = NULL;
// 	return (arr);
// }

// char	**split_by_quotes(char *token)
// {
// 	char	**arr;
// 	char	in_quote;
// 	int		k;
// 	int		i;
// 	int		j;
// 	int		segment_count;

// 	// Count all segments (quoted + non-quoted)
// 	segment_count = 0;
// 	i = 0;
// 	while (token[i])
// 	{
// 		segment_count++;
// 		if (ft_inset(token[i], "\'\""))
// 		{
// 			in_quote = token[i++];
// 			while (token[i] && token[i] != in_quote)
// 				i++;
// 			if (token[i] == in_quote)
// 				i++;
// 		}
// 		else
// 		{
// 			while (token[i] && !ft_inset(token[i], "\'\""))
// 				i++;
// 		}
// 	}

// 	arr = malloc(sizeof(char *) * (segment_count + 1));
// 	if (!arr)
// 		return (NULL);
	
// 	i = 0;
// 	k = 0;
// 	in_quote = 0;
// 	while (token[i])
// 	{
// 		j = 0;
// 		if (ft_inset(token[i], "\'\""))
// 		{
// 			in_quote = token[i];
// 			j = 1; // Skip opening quote
// 			while (token[i + j] && token[i + j] != in_quote)
// 				j++;
// 			if (token[i + j] == in_quote)
// 			{
// 				arr[k] = ft_substr(token, i + 1, j - 1); // Exclude quotes
// 				if (arr[k])
// 					k++;
// 				i += j + 1; // Move past closing quote
// 			}
// 			else
// 			{
// 				// Unmatched quote - take rest of string
// 				arr[k] = ft_substr(token, i + 1, j);
// 				if (arr[k])
// 					k++;
// 				i += j + 1;
// 			}
// 			in_quote = 0;
// 		}
// 		else
// 		{
// 			while (token[i + j] && !ft_inset(token[i + j], "\'\""))
// 				j++;
// 			arr[k] = ft_substr(token, i, j);
// 			if (arr[k])
// 				k++;
// 			i += j;
// 		}
// 	}
// 	arr[k] = NULL;
// 	return (arr);
// }

char	**split_by_quotes(char *token)
{
	char	**arr;
	char	in_quote;
	int		k;
	int		i;
	int		j;
	int		segment_count;

	// First, count total segments (quoted + non-quoted)
	segment_count = 0;
	i = 0;
	while (token[i])
	{
		segment_count++;
		if (ft_inset(token[i], "\'\""))
		{
			in_quote = token[i++];
			while (token[i] && token[i] != in_quote)
				i++;
			if (token[i] == in_quote)
				i++; // Skip closing quote
		}
		else
		{
			while (token[i] && !ft_inset(token[i], "\'\""))
				i++;
		}
	}

	arr = malloc(sizeof(char *) * (segment_count + 1));
	if (!arr)
		return (NULL);
	
	// Now extract segments
	i = 0;
	k = 0;
	while (token[i] && k < segment_count)
	{
		j = 0;
		if (ft_inset(token[i], "\'\""))
		{
			in_quote = token[i];
			j = 1; // Include opening quote
			while (token[i + j] && token[i + j] != in_quote)
				j++;
			if (token[i + j] == in_quote)
				j++; // Include closing quote
			
			arr[k] = ft_substr(token, i, j);
			if (!arr[k])
			{
				// Free previously allocated strings on failure
				while (k > 0)
					free(arr[--k]);
				free(arr);
				return (NULL);
			}
			k++;
			i += j;
		}
		else
		{
			while (token[i + j] && !ft_inset(token[i + j], "\'\""))
				j++;
			arr[k] = ft_substr(token, i, j);
			if (!arr[k])
			{
				while (k > 0)
					free(arr[--k]);
				free(arr);
				return (NULL);
			}
			k++;
			i += j;
		}
	}
	arr[k] = NULL; // NULL terminate the array
	return (arr);
}

static void	expand_command_variables(t_ast *ast, t_shell *shell)
{
	int i;
	int j;
	int expand;
	char *temp;
	char *res;
	char **arr;

	i = -1;
	while (ast->cmd->args && ast->cmd->args[++i])
	{
		j = -1;
		arr = split_by_quotes(ast->cmd->args[i]);
		free(ast->cmd->args[i]);
		ast->cmd->args[i] = ft_strdup("");
		while (arr[++j])
		{
			expand = 1;
			if (arr[j][0] == '\'')
				expand = 0;
			temp = expand_nested_quote(arr[j], has_heredoc(ast->cmd));
			res = expand_dollar_token(temp, shell, expand);
			free(arr[j]);
			arr[j] = ft_strdup(res);
			free(temp);
			free(res);
			temp = ft_strjoin(ast->cmd->args[i], arr[j]);
			free(ast->cmd->args[i]);
			ast->cmd->args[i] = temp;
		}
		free_split(arr);
	}
	free(ast->cmd->cmd_name);
	ast->cmd->cmd_name = ft_strdup(ast->cmd->args[0]);
}

int	execute_command(t_ast *ast, t_shell *shell, bool wait, int extra_fd)
{
	int status;

	expand_command_variables(ast, shell);
	printf("this ois [%s]\n", ast->cmd->cmd_name);
	int i = -1;
	while (ast->cmd->args[++i])
		printf("args = [%s]\n", ast->cmd->args[i]);
	update_env_var(ast, shell);
	if (ast->cmd->cmd_name && ft_strcmp(ast->cmd->cmd_name,
			"./minishell") == 0)
		shlvl_exec(shell, 1);
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
	pid_t pid;
	int exit_code;
	int status;

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
	int exit_code;

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
