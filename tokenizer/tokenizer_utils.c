/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:10:31 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/08/16 22:17:01 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	free_token_list(t_token **head)
{
	t_token	*current;
	t_token	*next;

	if (!head)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		free(current->token);
		free(current);
		current = next;
	}
	*head = NULL;
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
	while (value[++i])
		if (tk_inset(value[i], "`\\"))
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
	else if (tk_inset(*value, "\'\""))
		return (get_quoted_token_type(value));
	if (parenthesis_type == -1 && tk_inset(*value, "<>()"))
		return (TK_ERROR);
	else if (parenthesis_type != -1 && tk_inset(*value, "<>()"))
		return (parenthesis_type);
	return (TK_WORD);
}

void	add_token(t_token **head, char *value)
{
	t_token	*temp;
	t_token	*new_node;

	if (!value || !*value)
		return ;
	if (!(*head))
	{
		(*head) = (t_token *)malloc(sizeof(t_token));
		if (!(*head))
		{
			free(value);
			return ;
		}
		(*head)->token = value;
		(*head)->token_type = get_token_type(value);
		(*head)->next = NULL;
	}
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		new_node = (t_token *)malloc(sizeof(t_token));
		if (!new_node)
		{
			free(value);
			return ;
		}
		new_node->next = NULL;
		new_node->token = value;
		new_node->token_type = get_token_type(value);
		temp->next = new_node;
	}
}
