/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/10/09 18:19:07 by apatvaka          #+#    #+#             */
/*   Updated: 2025/10/09 18:19:07 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenizer.h"

/*
void	print_redir_cmd(t_redir_cmd *cmd)
{
	t_redir *r;

	while (cmd)
	{
		r = cmd->redirs;
		if (r)
			printf("redirections:\n");
		while (r)
		{
			if (r->type == TK_REDIR_INPUT)
				printf("  <  %s\n", r->filename);
			else if (r->type == TK_REDIR_OUTPUT)
				printf("  >  %s\n", r->filename);
			else if (r->type == TK_APPEND)
				printf("  >> %s\n", r->filename);
			else if (r->type == TK_HEREDOC)
				printf("  << %s\n", r->filename);
			r = r->next;
		}
		printf("\n");
		cmd = cmd->next;
	}
}
*/

t_redir_cmd	*parse_redirs(t_token **list)
{
	t_redir_cmd	*cmd;
	t_redir_cmd	*head;

	cmd = init_redir_cmd();
	if (!cmd)
		return (NULL);
	head = cmd;
	while ((*list))
	{
		if ((*list)->token_type == TK_WORD)
			add_arg(cmd, (*list)->token);
		else if (is_redir((*list)))
		{
			if (!(*list)->next || (*list)->next->token_type != TK_WORD)
				return (ft_putstr_fd("Syntax error near redir.\n", 2), NULL);
			add_redir(cmd, (*list)->token_type, (*list)->next->token);
			(*list) = (*list)->next;
		}
		else
			break ;
		(*list) = (*list)->next;
	}
	return (head);
}
