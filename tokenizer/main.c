/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:51:03 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/08/19 17:37:54 by rbarkhud         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	// t_env	*env;
	t_token	*token_list;
	t_ast	*ast;

	(void)argc;
	(void)envp;
	(void)argv;
	// (void)env;
	while (true)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		// env = parse_environment(envp);
		token_list = tokenize(line);
		add_history(line);
		if (token_list)
		{
			print_token_list(token_list);
			ast = build_ast(&token_list);
			// if (analyze(token_list))
			// 	printf("Syntax analysis passed.\n");
			// else
			// 	printf("Syntax analysis failed.\n");
			// print_ast(ast, 0);
			// if (execute_ast(ast, env))
			// 	perror("Execution failed");
			// else
			// 	printf("Execution successful.\n");
			free_ast(ast);
			// free_token_list(&token_list);
		}
		else
			printf("Tokenization failed.\n");
		// free_env_list(env);
		free(line);
	}
	rl_clear_history();
	return (0);
}
