/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:51:03 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/16 00:39:40 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

volatile sig_atomic_t	g_status;

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = init_shell_struct(envp);
	if (!shell)
		return (perror("minishell"), EXIT_FAILURE);
	minishell_loop(shell);
	free_shell(shell, 0);
	rl_clear_history();
	return (0);
}
