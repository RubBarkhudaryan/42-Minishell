/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:51:03 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/10/24 01:44:02 by rbarkhud         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*env;
	t_token	*token_list;
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (perror("malloc"), 1);
	env = parse_environment(envp);
	shell->env = env;
	shell->ast = NULL;
	shell->last_exit_code = 0;
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
		free(line);
	}
	free_shell(shell, 0);
	rl_clear_history();
	return (0);
}
