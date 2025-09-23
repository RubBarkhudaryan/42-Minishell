/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/09/02 17:47:33 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/09/02 17:47:33 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenizer.h"


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

t_redir_cmd	*parse_redirs(t_token **token_list)
{
	t_redir_cmd *cmd;
	t_redir_cmd *head;

	cmd = init_redir_cmd();
	if (!cmd)
		return (NULL);
	head = cmd;
	while ((*token_list))
	{
		if ((*token_list)->token_type == TK_WORD)
			add_arg(cmd, (*token_list)->token);
		else if (is_redir((*token_list)))
		{
			if (!(*token_list)->next || (*token_list)->next->token_type != TK_WORD)
				return (ft_putstr_fd("Syntax error near redir.", 2), NULL);
			add_redir(cmd, (*token_list)->token_type, (*token_list)->next->token);
			(*token_list) = (*token_list)->next;
		}
		else
			break ;
		(*token_list) = (*token_list)->next;
	}
	return (head);
}
