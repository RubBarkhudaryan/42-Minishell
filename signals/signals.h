/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:48:09 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/09/23 17:48:09 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H

# define SIGNALS_H

# include <signal.h>
# include "../tokenizer/tokenizer.h"

typedef struct s_shell			t_shell;
extern volatile sig_atomic_t	g_status;

void	parent_sigint_handler(int signo);
void	setup_signals(void);
void	setup_child_signals(void);
void	setup_heredoc_signals(void);
void	reset_signals(void);
void	ignore_signals(void);
void	check_exit_status(t_shell *shell);

#endif