/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:31:38 by apatvaka          #+#    #+#             */
/*   Updated: 2025/10/30 18:31:38 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenizer/tokenizer.h"

t_redir	*init_redir(int type, char *filename)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->filename = ft_strdup(filename);
	if (!redir->filename)
		return (free(redir), NULL);
	redir->type = type;
	redir->next = NULL;
	redir->is_expanded = 1;
	redir->heredoc_fd = -1;
	return (redir);
}

void	add_redir(t_redir *redirs, t_redir *new_node)
{
	t_redir	*temp;

	if (!new_node)
		return ;
	if (!redirs)
		redirs = new_node;
	else
	{
		temp = redirs;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}
