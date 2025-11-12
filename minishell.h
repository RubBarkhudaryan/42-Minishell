/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 03:34:27 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/13 03:34:27 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "./tokenizer/tokenizer.h"

void	free_shell(t_shell *shell, int flag_unlink_heredoc);
t_shell	*init_shell_struct(char **envp);
void	adding_redirs(t_ast *ast, t_shell *shell);
void	minishell_loop_logic(t_shell *shell, t_token *token_list);
void	minishell_loop(t_shell *shell);

#endif