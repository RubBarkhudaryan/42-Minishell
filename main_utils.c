/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 20:30:35 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/23 20:30:35 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
void	print_token_list(t_token *head)
{
	while (head)
	{
		printf("token: %s type: %d\n", head->token, head->type);
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

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (perror("malloc"), NULL);
	shell->env = parse_environment(envp);
	if (!shell->env)
		return (free(shell), NULL);
	shell->ast = NULL;
	shell->last_exit_code = 0;
	shell->interactive = true;
	shlvl_exec(shell);
	return (shell);
}

void	find_heredoc_in_ast(t_ast *ast, t_shell *shell)
{
	if (!ast)
		return ;
	find_heredoc_in_ast(ast->left, shell);
	if (ast->cmd && ast->cmd->redirs_cmd
		&& ast->cmd->redirs_cmd->type == TK_HEREDOC)
		process_heredocs(ast->cmd, shell);
	find_heredoc_in_ast(ast->right, shell);
}

void	minishell_loop_logic(t_shell *shell, t_token *lst)
{
	t_token	*tmp;

	if (lst)
	{
		tmp = lst;
		shell->token_list = lst;
		shell->ast = build_ast(&tmp, shell);
		find_heredoc_in_ast(shell->ast, shell);
		if (!shell->ast || check_quoted_str(lst))
		{
			shell->last_exit_code = 2;
			if (shell->ast)
				free_ast(shell->ast, 0);
			shell->ast = NULL;
		}
		free_token_list(shell->token_list);
		if (shell->ast)
		{
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
		line = readline("\001\033[1;32m\002🦂 minishell ֏ \001\033[0m\002");
		check_exit_status(shell);
		if (!line)
		{
			ft_putstr_fd("exit\n", 2);
			break ;
		}
		if (line[0])
		{
			add_history(line);
			token_list = tokenize(line);
			minishell_loop_logic(shell, token_list);
		}
		free(line);
	}
}
