/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:51:03 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/07/17 01:48:58 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./tokenizer.h"

void print_token_list(t_token *head)
{
	while (head)
	{
		printf("token: '%s', type: %d\n", head->token, head->token_type);
		head = head->next;
	}
}

/*
int main()
{
	char *input = "echo -n 'hello' > output.txt || grep \"hello\" && ls -l";
	t_token *t_list = tokenize(input);
	if (!t_list) {
		printf("Tokenization failed.\n");
		return 1;
	}
	print_token_list(t_list);
}
*/

int main()
{

	char *inputs[] = {
		"echo -n hello > output.txt | grep hello && ls -l",
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