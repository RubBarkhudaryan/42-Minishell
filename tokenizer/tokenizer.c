/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:56:45 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/07/28 20:28:29 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static int	get_quoted_token_type(char *value)
{
	int	len;

	len = tk_strlen(value);
	if (len >= 2 && value[0] == '\'' && value[len - 1] == '\'')
		return (TK_SINGLE_QUOTE);
	if (len >= 2 && value[0] == '\"' && value[len - 1] == '\"')
		return (TK_DOUBLE_QUOTE);
	return (TK_ERROR);
}

int	get_parenthesis_token_type(char *value)
{
	if (tk_strlen(value) == 1 && *value == '(')
		return (TK_L_PARENTHESIS);
	else if (tk_strlen(value) == 1 && *value == ')')
		return (TK_R_PARENTHESIS);
	else if (tk_strcmp("<<", value) == 0)
		return (TK_HEREDOC);
	else if (tk_strcmp(">>", value) == 0)
		return (TK_APPEND);
	else if (tk_strlen(value) == 1 && *value == '>')
		return (TK_REDIR_OUTPUT);
	else if (tk_strlen(value) == 1 && *value == '<')
		return (TK_REDIR_INPUT);
	return (TK_WORD);
}

int	get_token_type(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (tk_inset(value[i], "`\\"))
			return (TK_ERROR);
		++i;
	}
	if (tk_isalpha(value[0]) || (tk_strlen(value) >= 2 && *value == '-'))
		return (TK_WORD);
	else if (tk_strlen(value) == 1 && *value == '|')
		return (TK_PIPE);
	else if (tk_strlen(value) == 1 && *value == '$')
		return (TK_DOLLAR);
	else if (tk_strcmp("&&", value) == 0)
		return (TK_AND);
	else if (tk_strcmp("||", value) == 0)
		return (TK_OR);
	else if (tk_inset(*value, "\'\""))
		return (get_quoted_token_type(value));
	return (get_parenthesis_token_type(value));
}

void	add_token(t_token **head, char *value)
{
	t_token	*temp;
	t_token	*new_node;

	if (!value || !*value || tk_strlen(value) == 0)
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
	t_token	*head;

	i = 0;
	head = NULL;
	while (str[i])
	{
		while (str[i] && tk_isspace(str[i]))
			++i;
		if (str[i] == '\'' || str[i] == '\"')
			i = make_quoted_token(&head, str, i);
		else if (tk_isalpha(str[i]) || tk_inset(str[i],
				"!@#$%^*-_+=~`;\\/0123456789"))
			i = make_word_token(&head, str, i);
		else if (tk_inset(str[i], "|&<>()"))
			i = make_specials_token(&head, str, i);
		else
			++i;
	}
	return (head);
}
