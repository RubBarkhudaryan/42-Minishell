/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:10:31 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/08/26 17:13:24 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	free_token_list(t_token *head)
{
	t_token	*next;

	if (!head)
		return ;
	while (head)
	{
		next = head->next;
		free(head->token);
		free(head);
		head = next;
	}
}

int	get_quoted_token_type(char *value)
{
	int	len;

	len = ft_strlen(value);
	if (len >= 2 && value[0] == '\'' && value[len - 1] == '\'')
		return (TK_SINGLE_QUOTE);
	if (len >= 2 && value[0] == '\"' && value[len - 1] == '\"')
		return (TK_DOUBLE_QUOTE);
	return (TK_ERROR);
}

int	get_parenthesis_token_type(char *value)
{
	if (ft_strlen(value) == 1 && *value == '(')
		return (TK_L_PARENTHESIS);
	else if (ft_strlen(value) >= 1 && *value == ')')
		return (TK_R_PARENTHESIS);
	else if (ft_strcmp("<<", value) == 0)
		return (TK_HEREDOC);
	else if (ft_strcmp(">>", value) == 0)
		return (TK_APPEND);
	else if (ft_strlen(value) == 1 && *value == '>')
		return (TK_REDIR_OUTPUT);
	else if (ft_strlen(value) == 1 && *value == '<')
		return (TK_REDIR_INPUT);
	return (-1);
}

int	get_token_type(char *value)
{
	int	i;
	int	parenthesis_type;

	i = -1;
	parenthesis_type = get_parenthesis_token_type(value);
	if (ft_inset(*value, "\'\""))
		return (get_quoted_token_type(value));
	while (value[++i])
		if (ft_inset(value[i], "`\\;"))
			return (TK_ERROR);
	if (ft_isalpha(value[0]) || (ft_strlen(value) >= 2 && *value == '-'))
		return (TK_WORD);
	else if (ft_strlen(value) == 1 && *value == '|')
		return (TK_PIPE);
	else if (ft_strlen(value) > 1 && *value == '$')
		return (TK_DOLLAR);
	else if (ft_strcmp("&&", value) == 0)
		return (TK_AND);
	else if (ft_strcmp("||", value) == 0)
		return (TK_OR);
	if (parenthesis_type == -1 && ft_inset(*value, "<>()"))
		return (TK_ERROR);
	else if (parenthesis_type != -1 && ft_inset(*value, "<>()"))
		return (parenthesis_type);
	return (TK_WORD);
}

void	add_token(t_token **head, char *value)
{
	t_token	*temp;
	t_token	*new_node;

	if (!head || !value || !(*value))
		return ;
	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
	{
		free(value);
		return ;
	}
	new_node->next = NULL;
	new_node->token_type = get_token_type(value);
	new_node->token = value;
	if (!(*head))
		(*head) = new_node;
	else
	{
		temp = (*head);
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}
