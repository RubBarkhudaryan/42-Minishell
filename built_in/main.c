/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:10:01 by apatvaka          #+#    #+#             */
/*   Updated: 2025/07/17 23:50:51 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bulit_in.h"
#include <stdio.h>
#include <string.h>


// Helper to print a header before each test
void	print_test_header(int num, char **args)
{
	printf("\nTest %d: ", num);
	for (int i = 0; args[i]; i++)
		printf("\"%s\" ", args[i]);
	printf("Output: ");
}

int	main(void)
{
	char	*test1[] = {"echo", NULL};
	char	*test2[] = {"echo", "-n", "hello", "world", NULL };
	char	*test3[] = {"echo", "-nnn", "foo", NULL };

	char	**tests[] = {test1, test2, test3,  NULL};

	for (int i = 0; tests[i]; i++)
	{
		print_test_header(i + 1, tests[i]);
		ft_echo(tests[i]);
		// printf("\n"); // Add separation line after each test output
	}
	return (0);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <assert.h>
// #include "bulit_in.h"   // where ft_echo is declared

// #define GREEN  "\033[0;32m"
// #define RED    "\033[0;31m"
// #define YELLOW "\033[0;33m"
// #define RESET  "\033[0m"

// static int  test_count   = 0;
// static int  passed_tests = 0;

// /**
//  * run_test:
//  *   name      — human‑readable test name
//  *   args      — NULL‑terminated argv‑style array (omit the "echo" name)
//  *   expected  — expected printed string (without trailing newline,
//  *                unless you include it here)
//  *   add_nl    — set to 1 if you expect ft_echo to always append a '\n'
//  */
// void run_test(const char *name, char *args[], const char *expected, int add_nl)
// {
//     int   pipefd[2];
//     pid_t pid;
//     char  buf[1024];
//     ssize_t n;
//     char  exp_buf[1024];

//     // build expected buffer
//     if (add_nl)
//         snprintf(exp_buf, sizeof(exp_buf), "%s\n", expected);
//     else
//         strncpy(exp_buf, expected, sizeof(exp_buf));

//     // create pipe
//     assert(pipe(pipefd) == 0);

//     // fork so ft_echo prints into pipe
//     pid = fork();
//     if (pid < 0) {
//         perror("fork");
//         exit(1);
//     }
//     if (pid == 0) {
//         // child: redirect stdout -> pipe
//         close(pipefd[0]);
//         dup2(pipefd[1], STDOUT_FILENO);
//         close(pipefd[1]);
//         ft_echo(args);
//         _exit(0);
//     }
//     // parent: read child output
//     close(pipefd[1]);
//     n = read(pipefd[0], buf, sizeof(buf) - 1);
//     if (n < 0) {
//         perror("read");
//         exit(1);
//     }
//     buf[n] = '\0';
//     close(pipefd[0]);

//     test_count++;
//     if (strcmp(buf, exp_buf) == 0) {
//         printf(GREEN "✓ PASS" RESET " (%s)\n", name);
//         passed_tests++;
//     } else {
//         printf(RED "✗ FAIL" RESET " (%s)\n", name);
//         printf("    expected: \"%s\"\n", exp_buf);
//         printf("         got: \"%s\"\n", buf);
//     }
// }

// int main(void)
// {
//     printf(YELLOW "=== FT_ECHO TEST SUITE ===\n" RESET);

//     // NOTE: ft_echo argv normally includes argv[0] = "echo", but
//     //       here we assume your ft_echo treats args[] starting
//     //       directly at the first meaningful token.

//     char *t1[] = {"echo", NULL };
//     run_test("no args → newline", t1, "", 1);

//     char *t2[] = { "echo", "hello", "world", NULL };
//     run_test("basic echo", t2, "hello world", 1);

//     char *t3[] = {"echo", "-n", "hello", "world", NULL };
//     run_test("suppress newline", t3, "hello world", 0);

//     char *t4[] = {"echo", "-nnn", "foo", NULL };
//     run_test("multiple -n flags", t4, "foo", 0);

//     char *t5[] = {"echo", "-n", NULL };
//     run_test("only -n", t5, "", 0);

//     char *t6[] = {"echo", "foo", "-n", "bar", NULL };
//     run_test("-n in middle", t6, "foo -n bar", 1);

//     char *t7[] = {"echo", "-x", "hello", NULL };
//     run_test("invalid flag", t7, "-x hello", 1);

//     char *t8[] = {"echo", "-", "dash", NULL };
//     run_test("single dash", t8, "- dash", 1);

//     char *t9[] = {"echo", "--", "double", NULL };
//     run_test("double dash", t9, "-- double", 1);

//     printf("\n" YELLOW "Summary:" RESET " %d/%d passed\n",
//            passed_tests, test_count);

//     return (passed_tests == test_count) ? 0 : 1;
// }

