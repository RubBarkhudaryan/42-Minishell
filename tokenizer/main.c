/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:51:03 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/08/02 16:05:46 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../syntax_analysis/syntax.h"
#include <readline/history.h>
#include <readline/readline.h>

static void	print_token_list(t_token *head)
{
	while (head)
	{
		printf("token: %s type: %d\n", head->token, head->token_type);
		head = head->next;
	}
}

int	main(void)
{
	char	*line;
	t_token	*token_list;

	while (true)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		token_list = tokenize(line);
		add_history(line);
		if (token_list)
		{
			print_token_list(token_list);
			if (analyze(token_list))
				printf("Syntax analysis passed.\n");
			else
				printf("Syntax analysis failed.\n");
			free_token_list(token_list);
		}
		else
		{
			printf("Tokenization failed.\n");
		}
		free(line);
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