/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 03:33:00 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/13 03:33:00 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
void	print_token_list(t_token *head)
{
	while (head)
	{
		printf("token: %s type: %d\n", head->token, head->token_type);
		head = head->next;
	}
}
*/

void	free_shell(t_shell *shell, int flag_unlink_heredoc)
{
	if (shell->env)
		free_env_list(shell->env);
	if (shell->ast)
		free_ast(shell->ast, flag_unlink_heredoc);
	free(shell);
}

t_shell	*init_shell_struct(char **envp)
{
	t_shell	*shell;
	t_env	*env;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (perror("malloc"), NULL);
	env = parse_environment(envp);
	if (!env)
		return (free(shell), NULL);
	shell->env = env;
	shell->ast = NULL;
	shell->last_exit_code = 0;
	return (shell);
}

void	adding_redirs(t_ast *ast, t_shell *shell)
{
	if (!ast)
		return ;
	adding_redirs(ast->left, shell);
	if (ast->cmd && ast->cmd->token_list)
		ast->cmd = parse_redirs_ast(ast->cmd, &ast->cmd->token_list, shell);
	adding_redirs(ast->right, shell);
}

void	minishell_loop_logic(t_shell *shell, t_token *token_list)
{
	t_token	*tmp;

	if (token_list)
	{
		tmp = token_list;
		shell->token_list = token_list;
		shell->ast = build_ast(&tmp, shell);
		adding_redirs(shell->ast, shell);
		if (check_quoted_str(token_list) || validate_parenthesis(token_list))
		{
			free_ast(shell->ast, 0);
			shell->ast = NULL;
		}
		free_token_list(shell->token_list);
		if (shell->ast)
		{
			if (syntax_analyze(shell->ast))
				shell->last_exit_code = execute_node(shell);
			free_ast(shell->ast, 0);
			shell->ast = NULL;
		}
	}
}

void	minishell_loop(t_shell *shell)
{
	t_token	*token_list;
	char	*line;

	while (true)
	{
		setup_signals();
		line = readline("\001\033[1;32m\002🐍 minishell ֏ \001\033[0m\002");
		if (!line)
		{
			shlvl_exec(shell, 0);
			printf("exit\n");
			break ;
		}
		if (ft_strcmp(line, ""))
		{
			add_history(line);
			token_list = tokenize(line);
			minishell_loop_logic(shell, token_list);
		}
		if (g_status != 0)
			shell->last_exit_code = g_status;
		else
			g_status = shell->last_exit_code;
		free(line);
	}
}
