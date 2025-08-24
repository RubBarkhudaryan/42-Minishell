/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:51:03 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/08/24 21:26:57 by apatvaka         ###   ########.fr       */
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
	t_env	*env;
	t_token	*token_list;
	t_token	*token_list1;
	t_ast	*ast;

	ast = NULL;
	(void)argc;
	(void)envp;
	(void)argv;
	(void)env;
	while (true)
	{
		line = readline("minishell> ");
		if (!line || !(*line))
			break ;
		env = parse_environment(envp);
		token_list = tokenize(line);
		add_history(line);
		if (token_list)
		{
			token_list1 = token_list;
			print_token_list(token_list);
			ast = build_ast(&token_list);
			if (analyze(token_list))
				printf("Syntax analysis passed.\n");
			// else
			// 	printf("Syntax analysis failed.\n");
			if (execute_node(ast, env) == -1)
				perror("Execution failed");
			// else
			// 	printf("Execution successful.\n");
			print_ast(ast, 0);
			free_token_list(token_list1);
			free_ast(ast);
		}
		else
			printf("Tokenization failed.\n");
		free_env_list(env);
		free(line);
	}
	rl_clear_history();
	return (0);
}
