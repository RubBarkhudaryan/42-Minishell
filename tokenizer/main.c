/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:51:03 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/10/04 12:42:33 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

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
	free_env_list(shell->env);
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
	shell = NULL;
	// shell->last_exit_code = 0;
	env = parse_environment(envp);
	while (true)
	{
		init_signals();
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			break ;	
		}
		token_list = tokenize(line);
		add_history(line);
		if (token_list)
		{
			shell = malloc(sizeof(t_shell));
			if (!shell)
			{
				free_env_list(env);
				free_token_list(token_list);
				perror("minshell:");
				exit(1);
			}
			expand_tokens(&token_list);
			shell->token_list = token_list;
			shell->env = env;
			shell->ast = NULL;
			shell->ast = build_ast(&token_list, shell);
			if (!syntax_analyze(shell->ast))
			{
				printf("Syntax error\n");
				free_token_list(token_list);
				free(shell);
				free(line);
				continue ; // give the error code 2
			}
			free_token_list(shell->token_list);
			print_ast(shell->ast, 0);
			if (!shell->ast)
			{
				free_env_list(env);
				perror("minishell");
				exit(1);
			}
			shell->last_exit_code = execute_node(shell);
			free_ast(shell->ast, 1);
			free(shell);
		}
		else
			printf("Tokenization failed.\n");
		free(line);
	}
	free_env_list(env);
	rl_clear_history();
	return (0);
}
