/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:51:03 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/06 19:50:12 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./tokenizer/tokenizer.h"

/*
*/

void	print_token_list(t_token *head)
{
	while (head)
	{
		printf("token: %s type: %d\n", head->token, head->token_type);
		head = head->next;
	}
}
/*utils*/
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
		expand_tokens(&token_list);
		tmp = token_list;
		shell->token_list = token_list;
		shell->ast = build_ast(&tmp, shell);
		adding_redirs(shell->ast, shell);
		print_ast(shell->ast, 0);
		free_token_list(shell->token_list);
		if (shell->ast)
		{
			if (syntax_analyze(shell->ast))
				shell->last_exit_code = execute_node(shell);
			else
				shell->last_exit_code = 2;
			free_ast(shell->ast, 0);
			shell->ast = NULL;
		}
		else
			shell->last_exit_code = 2;
	}
}

void	minishell_loop(t_shell *shell)
{
	t_token	*token_list;
	char	*line;

	while (true)
	{
		line = readline("\001\033[1;32m\002🐍 minishell ֏ \001\033[0m\002");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		add_history(line);
		token_list = tokenize(line);
		minishell_loop_logic(shell, token_list);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	init_signals();
	shell = init_shell_struct(envp);
	if (!shell)
		return (perror("minishell"), EXIT_FAILURE);
	minishell_loop(shell);
	free_shell(shell, 0);
	rl_clear_history();
	return (0);
}
