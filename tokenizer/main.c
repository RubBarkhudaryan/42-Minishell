/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:51:03 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/07/28 18:45:12 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./tokenizer.h"
#include <readline/readline.h>

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
		if (token_list)
		{
			print_token_list(token_list);
			free_token_list(token_list);
		}
		else
		{
			printf("Tokenization failed.\n");
		}
		free(line);
	}
	return (0);
}

/*
int	main()
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
	return 0;

}
*/

/*
int main()
{
	char *argv[] = {"echo", "nested 'quotes' and | pipes", NULL};
	char *envp[] = {NULL};

	execve("/bin/echo", argv, envp);
	perror("execve failed");
	return 1;
}
*/