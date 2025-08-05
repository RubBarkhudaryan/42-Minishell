/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_maker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:52:28 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/08/05 20:32:45 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./tokenizer.h"

int	make_quoted_token(t_token **head, char *str, int i)
{
	int		j;
	char	quote;

	j = 1;
	quote = str[i];
	while (str[i + j])
	{
		if (str[i + j] == quote && str[i + j] != '\\')
			break ;
		++j;
	}
	if (str[i + j] == quote)
		++j;
	if (j != 0)
		add_token(head, tk_substr(str, i, j));
	printf("j = %d\n", j);
	return (i + j);
}

int	make_word_token(t_token **head, char *str, int i)
{
	int	j;

	j = 0;
	while (str[i + j])
	{
		if (tk_isalpha(str[i + j]) || tk_inset(str[i + j],
				"!@#$%^*-_+=~`;.?,{}[]\\/0123456789"))
			++j;
		else
			break ;
	}
	if (j != 0)
		add_token(head, tk_substr(str, i, j));
	return (i + j);
}

int	make_specials_token(t_token **head, char *str, int i)
{
	int	j;

	j = 0;
	while (str[i + j])
	{
		if (tk_inset(str[i + j], "|&<>"))
			++j;
		else
			break ;
	}
	if (j != 0)
		add_token(head, tk_substr(str, i, j));
	return (i + j);
}

int	parse_subshell(t_token **head, char *str, int i)
{
	int	l_count;
	int	r_count;
	int	is_alpha;
	int	new_i;

	l_count = 0;
	r_count = 0;
	is_alpha = 0;
	while (str[i])
	{
		if (str[i] == '(')
		{
			add_token(head, tk_substr(str, i, 1));
			++i;
			++l_count;
		}
		else if (!tk_inset(str[i], "()"))
		{
			is_alpha = 1;
			if (str[i] == '\'' || str[i] == '\"')
			{
				new_i = make_quoted_token(head, str, i);
				if (new_i != i)
				{
					i = new_i;
					continue ;
				}
			}
			else if (tk_inset(str[i], "|&<>"))
			{
				new_i = make_specials_token(head, str, i);
				if (new_i != i)
				{
					i = new_i;
					continue ;
				}
			}
			else
			{
				new_i = make_word_token(head, str, i);
				if (new_i != i)
				{
					i = new_i;
					continue ;
				}
			}
			++i;
		}
		else if (str[i] == ')')
		{
			while (str[i] && str[i] == ')')
			{
				++i;
				++r_count;
			}
			add_token(head, tk_substr(str, i - r_count, r_count));
		}
		else
			++i;
	}
	if (l_count == r_count && is_alpha)
		return (i);
	return (-1);
}
