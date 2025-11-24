/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:51:03 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/24 16:32:21 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

volatile sig_atomic_t	g_status;

void	free_shell(t_shell *shell, int flag_unlink_heredoc)
{
	if (shell->env)
		free_env_list(shell->env);
	if (shell->ast)
		free_ast(shell->ast, flag_unlink_heredoc);
	free(shell);
}

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
