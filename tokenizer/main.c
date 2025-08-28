/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:51:03 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/08/27 16:51:44 by rbarkhud         ###   ########.fr       */
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
			// print_token_list(token_list);
			if (analyze(token_list))
			{
				expand_tokens(&token_list, env);
				ast = build_ast(&token_list);
				if (ast)
				{
					// print_ast(ast, 0);
					if (execute_node(ast, env) == -1)
						perror("Execution failed");
				}
				free_token_list(token_list1);
				free_ast(ast);
			}
			else
				printf("Syntax analysis failed.\n");
		}
		else
			printf("Tokenization failed.\n");
		free_env_list(env);
		free(line);
	}
	rl_clear_history();
	return (0);
}
