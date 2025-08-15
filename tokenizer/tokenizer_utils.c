/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:10:31 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/08/06 14:55:45 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	free_token_list(t_token *head)
{
	t_token	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->token);
		free(temp);
	}
}

int	get_quoted_token_type(char *value)
{
	int	len;

	len = ft_strlen((const char *)value);
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
	while (value[++i])
		if (ft_inset(value[i], "`\\"))
			return (TK_ERROR);
	if (ft_isalpha(value[0]) || (ft_strlen(value) >= 2 && *value == '-'))
		return (TK_WORD);
	else if (ft_strlen(value) == 1 && *value == '|')
		return (TK_PIPE);
	else if (ft_strlen(value) == 1 && *value == '$')
		return (TK_DOLLAR);
	else if (ft_strcmp("&&", value) == 0)
		return (TK_AND);
	else if (ft_strcmp("||", value) == 0)
		return (TK_OR);
	else if (ft_inset(*value, "\'\""))
		return (get_quoted_token_type(value));
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

	if (!value || !*value || ft_strlen(value) == 0)
		return ;
	if (!(*head))
	{
		(*head) = (t_token *)malloc(sizeof(t_token));
		(*head)->token = value;
		(*head)->token_type = get_token_type(value);
		(*head)->next = NULL;
		return ;
	}
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		new_node = (t_token *)malloc(sizeof(t_token));
		new_node->next = NULL;
		new_node->token = value;
		new_node->token_type = get_token_type(value);
		temp->next = new_node;
	}
}
