/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:30:06 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/17 02:15:00 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenizer/tokenizer.h"

void	free_redir_list(t_redir *redir, int flag_unlink_heredoc)
{
	t_redir	*next;

	if (!redir)
		return ;
	while (redir)
	{
		next = redir->next;
		if (redir->type == TK_HEREDOC && flag_unlink_heredoc)
			unlink(redir->filename);
		free(redir->filename);
		free(redir);
		redir = next;
	}
}
