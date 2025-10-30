/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:51:03 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/10/30 18:43:21 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

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

void	minishell_loop_logic(t_shell *shell, t_token *token_list)
{
	if (token_list)
	{
		expand_tokens(&token_list);
		shell->token_list = token_list;
		shell->ast = build_ast(&token_list, shell);
		free_token_list(shell->token_list);
		if (shell->ast)
		{
			if (syntax_analyze(shell->ast))
				shell->last_exit_code = execute_node(shell);
			free_ast(shell->ast, 0);
			shell->ast = NULL;
		}
		else
			perror("minishell: AST build failed\n");
	}
}

void	minishell_loop(t_shell *shell)
{
	t_token	*token_list;
	char	*line;

	while (true)
	{
		init_signals();
		line = readline("minishell> ");
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
	shell = init_shell_struct(envp);
	if (!shell)
		return (perror("minishell"), EXIT_FAILURE);
	minishell_loop(shell);
	free_shell(shell, 0);
	rl_clear_history();
	return (0);
}
