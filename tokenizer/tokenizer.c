/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:56:45 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/07/17 18:23:37 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	get_parenthesis_token_type(char *value)
{
	if (ft_strlen(value) == 1 && *value == '(')
		return (TK_L_PARENTHESIS);
	else if (ft_strlen(value) == 1 && *value == ')')
		return (TK_R_PARENTHESIS);
	else if (ft_strcmp("<<", value) == 0)
		return (TK_HEREDOC);
	else if (ft_strcmp(">>", value) == 0)
		return (TK_APPEND);
	else if (ft_strlen(value) == 1 && *value == '>')
		return (TK_REDIR_OUTPUT);
	else if (ft_strlen(value) == 1 && *value == '<')
		return (TK_REDIR_INPUT);
	return (TK_ERROR);
}

int	get_token_type(char *value)
{
	if (ft_isalpha(value[0]) || (ft_strlen(value) >= 2 && *value == '-'))
		return (TK_WORD);
	else if (ft_strlen(value) == 1 && *value == '|')
		return (TK_PIPE);
	else if (ft_strlen(value) == 1 && *value == '$')
		return (TK_DOLLAR);
	else if (ft_strlen(value) >= 1 && *value == '\'')
	{
		if (value[0] == '\'' && value[ft_strlen(value) - 1] == '\'')
			return (TK_SINGLE_QUOTE);
		return (TK_ERROR);
	}
	else if (ft_strlen(value) >= 1 && *value == '\"')
	{
		if (value[0] == '\'' && value[ft_strlen(value) - 1] == '\'')
			return (TK_DOUBLE_QUOTE);
		return (TK_ERROR);
	}
	else if (ft_strcmp("&&", value) == 0)
		return (TK_AND);
	else if (ft_strcmp("||", value) == 0)
		return (TK_OR);
	return (get_parenthesis_token_type(value));
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

t_token	*tokenize(char *str)
{
	int		i;
	int		j;
	t_token	*head;

	i = 0;
	head = NULL;
	while (str[i])
	{
		j = 0;
		while (str[i] && ft_isspace(str[i]))
			++i;
		if (str[i] == '\'' || str[i] == '\"')
			i = make_quoted_token(&head, str, i);
		else if (ft_isalpha(str[i + j]) || ft_inset(str[i + j],
				"^-_*.$+=\\0123456789"))
			i = make_word_token(&head, str, i);
		else if (ft_inset(str[i + j], "|&<>();"))
			i = make_specials_token(&head, str, i);
		else
			++i;
	}
	return (head);
}
