/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:55:35 by apatvaka          #+#    #+#             */
/*   Updated: 2025/10/10 19:46:59 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast.h"

t_token	*find_matching_parenthesis(t_token *start)
{
	int		count;
	t_token	*current;

	count = 0;
	current = start;
	while (current != NULL)
	{
		if (current->token_type == TK_L_PARENTHESIS)
			count++;
		else if (current->token_type == TK_R_PARENTHESIS)
		{
			count--;
			if (count == 0)
				return (current);
		}
		current = current->next;
	}
	return (NULL);
}

int	count_args(t_token *current)
{
	int	count;

	count = 0;
	while (current && is_valid_token_type(current->token_type))
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	set_type(t_ast *node, int type)
{
	if (type == TK_OR)
		node->type = NODE_OR;
	else
		node->type = NODE_AND;
}

void	set_cmd(t_ast *node)
{
	node->cmd = malloc(sizeof(t_cmd));
	node->cmd->args = NULL;
	node->cmd->cmd_name = NULL;
	node->cmd->redirs_cmd = NULL;
	node->cmd->in_pipeline = -1;
	node->cmd->out_pipeline = -1;
}
