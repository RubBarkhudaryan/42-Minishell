/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:51:03 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/09/17 20:03:14 by apatvaka         ###   ########.fr       */
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
// utils
void	free_shell(t_shell *shell)
{
	free_env_list(shell->env);
	free_token_list(shell->token_list);
	free_ast(shell->ast);
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
	env = parse_environment(envp);
	while (true)
	{
		line = readline("minishell> ");
		if (!line || !(*line))
			break ;
		printf("line %s", line);
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
			shell->token_list = token_list;
			analyze(token_list);
			// print_token_list(token_list);
			shell->env = env;
			shell->ast = NULL;
			shell->last_exit_code = 0;
			shell->ast  = build_ast(&token_list, shell);
			free_token_list(shell->token_list);
			print_ast(shell->ast, 0);
			if (!shell->ast)
			{
				free_env_list(env);
				perror("minishell");
				exit(1);
			}
			printf("exit code %d\n\n\n", execute_node(shell));
			free_ast(shell->ast);
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
