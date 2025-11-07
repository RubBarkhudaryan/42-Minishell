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

extern volatile sig_atomic_t g_status;

void	init_signals(void);
void	handle_heredoc_signals(void);
void	sigint_handler_parent(int signo);

#endif