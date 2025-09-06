/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:51:03 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/09/06 14:32:43 by rbarkhud         ###   ########.fr       */
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
	free_ast(shell->ast);
	free(shell);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_env		*env;
	t_token		*token_list;
	t_token		*token_list1;
	t_ast		*ast;
	t_shell		*shell;
	t_redir_cmd	*cmd;

	(void)argc;
	(void)argv;
	ast = NULL;
	shell = NULL;
	env = parse_environment(envp);
	while (true)
	{
		line = readline("minishell> ");
		if (!line || !(*line))
			break ;
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
			token_list1 = token_list;
			cmd = parse_redirs(token_list);
			print_redir_cmd(cmd);
			// print_token_list(token_list);
			ast = build_ast(&token_list);
			if (!ast)
			{
				free_token_list(token_list1);
				free_env_list(env);
				perror("minishell");
				exit(1);
			}
			free_token_list(token_list1);
			free_redir_cmd(cmd);
			shell->ast = ast;
			shell->env = env;
			analyze(token_list);
			execute_node(shell);
			free_shell(shell);
		}
		else
			printf("Tokenization failed.\n");
		free(line);
	}
	free_env_list(env);
	rl_clear_history();
	return (0);
}
