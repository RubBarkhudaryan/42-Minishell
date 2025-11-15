/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:10:31 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/15 19:55:01 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	check_quoted_token_type(char *value)
{
	int		i;
	int		quote;
	char	q;

	i = 0;
	quote = 0;
	q = ' ';
	while (value[i])
	{
		if (!quote && ft_inset(value[i], "\'\""))
		{
			quote = 1;
			q = value[i];
		}
		else if (quote && ft_inset(value[i], "\'\"") && q == value[i])
		{
			quote = 0;
			q = ' ';
		}
		++i;
	}
	if (ft_inset(q, "\'\""))
		return (TK_ERROR);
	return (TK_WORD);
}

void	free_token_list(t_token *head)
{
	t_token	*next;

	if (!head)
		return ;
	while (head)
	{
		next = head->next;
		if (head->token)
		{
			free(head->token);
			head->token = NULL;
		}
		free(head);
		head = NULL;
		head = next;
	}
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
	{
		if (ft_inset(value[i], "`;"))
			return (TK_ERROR);
	}
	if (ft_isalpha(value[0]) || (ft_strlen(value) >= 2 && *value == '-'))
		return (TK_WORD);
	else if (ft_strlen(value) == 1 && *value == '|')
		return (TK_PIPE);
	else if (ft_strcmp("&&", value) == 0)
		return (TK_AND);
	else if (ft_strcmp("||", value) == 0)
		return (TK_OR);
	if (parenthesis_type == -1 && ft_inset(*value, "<>()"))
		return (TK_ERROR);
	else if (parenthesis_type != -1 && ft_inset(*value, "<>()"))
		return (parenthesis_type);
	return (check_quoted_token_type(value));
}
