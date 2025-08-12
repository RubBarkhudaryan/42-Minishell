/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:40:25 by apatvaka          #+#    #+#             */
/*   Updated: 2025/08/12 18:55:07 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	find_cmd_in_path(char **path, char *token, char *cmd)
{
	char	*tmp1;
	char	*tmp2;
	int		i;

	i = -1;
	while (path[++i])
	{
		tmp1 = ft_strjoin(path[i], "/");
		if (!tmp1)
			return (-1); // malloc fail
		tmp2 = ft_strjoin(path[i], token);
		if (!tmp2)
			return (free(tmp1), -1);
		if (access(tmp2, X_OK))
			return (free(tmp1), cmd = tmp2, 0);
		free(tmp1);
		free(tmp2);
	}
	return (1);
}

int	execute_command(t_ast *ast, t_env *env)
{
	char	**path;
	char	*cmd_path;

	cmd_path = NULL;
	path = ft_split(get_value_from_env(env, "PATH"), ':'); // free thissss
	if (!path)
		return (127);
	if (find_cmd_in_path(path, ast->cmd->token, cmd_path))
		return (127);
	execve(cmd_path, cmd, convert_envp_to_string(env));
	return (1);
}

int	execute_ast(t_ast *ast, t_env *env)
{
	if (!ast)
		return (0);
	// if (ast->type == NODE_AND)
	// 	return (execute_ast(ast->left, env) && execute_ast(ast->right, env));
	// else if (ast->type == NODE_OR)
	// 	return (execute_ast(ast->left, env) || execute_ast(ast->right, env));
	// else if (ast->type == NODE_PIPE)
	// 	return (execute_pipe(ast, env));
	// else
	if (ast->type == NODE_COMMAND)
		return (execute_command(ast, env));
	return (0);
}
