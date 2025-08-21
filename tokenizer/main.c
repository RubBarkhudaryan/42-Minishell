/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:51:03 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/08/21 21:09:24 by apatvaka         ###   ########.fr       */
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
	t_token	*token_list2;
	t_ast	*ast;

	(void)argc;
	(void)envp;
	(void)argv;
	(void)env;
	while (true)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		env = parse_environment(envp);
		token_list = tokenize(line);
		token_list2 = token_list;
		add_history(line);
		if (token_list)
		{
			print_token_list(token_list);
			ast = build_ast(&token_list);
			if (analyze(token_list))
				printf("Syntax analysis passed.\n");
			else
				printf("Syntax analysis failed.\n");
			print_ast(ast, 0);
			if (execute_ast(ast, env))
				perror("Execution failed");
			else
				printf("Execution successful.\n");
			free_ast(ast);
			free_token_list(&token_list2);
		}
		else
			printf("Tokenization failed.\n");
		free_env_list(env);
		free(line);
	}
	rl_clear_history();
	return (0);
}
