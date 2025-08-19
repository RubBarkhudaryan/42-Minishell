/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:51:03 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/08/18 18:36:09 by apatvaka         ###   ########.fr       */
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
		add_history(line);
		if (token_list)
		{
			print_token_list(token_list);
			ast = build_ast(&token_list);
			// print_ast(ast, 0);
			// if (analyze(token_list))
			// 	printf("Syntax analysis passed.\n");
			// else
			// 	printf("Syntax analysis failed.\n");
			// print_ast(ast, 0);
			if (execute_ast(ast, env))
				perror("Execution failed");
			else
				printf("Execution successful.\n");
			free_ast(ast);
		}
		else
			printf("Tokenization failed.\n");
		free(line);
		free_env_list(env);
	}
	rl_clear_history();
	return (0);
}

/*
int	main(void)
{
	char *inputs[] = {
		"ls -l > output.txt | grep hello && ls -l",
		"ls",
		"cat < infile | sort > outfile",
		"echo \"hello world\" && echo '42'",
		"ls -l | grep '^d' > dirs.txt",
		"echo foo\\ bar",
		"echo \"a | b && c\"",
		"echo 'single quoted > | && <'",
		"echo \"nested 'quotes' and | pipes\"",
		"ls; pwd && whoami",
		"echo >file1 <file2",
		"echo \"unclosed quote",
		"echo 'another unclosed",
		"echo \"escaped \\\" quote\"",
		"echo 'escaped \\' quote'",
		"$(echo Hello; echo World)",
		"$$",
		"(((())))",
		"echo hello\"fghjkl\"",
		"export var=100",
		"export var+=\"100\"",
		NULL
	};
	for (int i = 0; inputs[i]; i++)
	{
		printf("Test case %d: %s\n\n", i + 1, inputs[i]);
		print_token_list(tokenize(inputs[i]));
		printf("\n\n");
	}
	return (0);
}
*/

/*
int	main(void)
{
	char	*argv[] = {"echo", "nested 'quotes' and | pipes", NULL};
	char	*envp[] = {NULL};

	execve("/bin/echo", argv, envp);
	perror("execve failed");
	return (1);
}
*/
