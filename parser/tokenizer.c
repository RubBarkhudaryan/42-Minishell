/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:56:45 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/07/17 02:48:36 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	handle_quoted_token(t_token **head, char *str, int i)
{
	int	j;

	j = 0;
	if (str[i] == '\'' || str[i] == '\"')
	{
		char quote = str[i];
		++j;
		while (str[i + j] && str[i + j] != quote)
			++j;
		if (str[i + j] == quote)
			++j;
		add_token(head, ft_substr(str, i, j));
		return (i + j);
	}
	return (i);
}

int	get_parenthesis_token_type(char *value)
{
	if (ft_strlen(value) == 1 && *value == '(')
		return (TK_L_PARENTHESIS);
	else if (ft_strlen(value) == 1 && *value == ')')
		return (TK_R_PARENTHESIS);
	else if(ft_strcmp("<<", value) == 0)
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
	if (ft_isalpha(value[0]))
		return (TK_WORD);
	else if (ft_strlen(value) == 1 && *value == '|')
		return (TK_PIPE);
	else if (ft_strlen(value) == 1 && *value == ';')
		return (TK_SEMI_COLON);
	else if (ft_strlen(value) == 1 && *value == '$')
		return (TK_DOLLAR);
	else if (ft_strlen(value) >= 2 && *value == '-')
		return (TK_FLAG_SIGN);
	else if (ft_strlen(value) >= 1 && *value == '\'')
		return (TK_SINGLE_QUOTE);
	else if (ft_strlen(value) >= 1 && *value == '\"')
		return (TK_DOUBLE_QUOTE);
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
			i = handle_quoted_token(&head, str, i);
		while (str[i + j] && (ft_isalpha(str[i + j]) || ft_inset(str[i + j], "^-_*.$\\0123456789")))
			++j;
		if (j > 0)
		{
			add_token(&head, ft_substr(str, i, j));
			i += j;
			j = 0;
		}
		while (str[i + j] && ft_inset(str[i + j], "|&<>();"))
			++j;
		if (j > 0)
		{
			add_token(&head, ft_substr(str, i, j));
			i += j;
		}
	}
	return (head);
}

