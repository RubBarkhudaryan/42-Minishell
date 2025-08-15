/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:49:19 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/08/15 20:48:32 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./tokenizer.h"

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
			add_token(head, ft_substr(str, i, 1));
			++i;
			++l_count;
		}
		else if (str[i] == ')')
		{
			while (str[i] && str[i] == ')')
			{
				++i;
				++r_count;
			}
			add_token(head, ft_substr((const char *)str, i - r_count, r_count));
		}
		else
			++i;
	}
	if (l_count == r_count && is_alpha)
		return (i);
	return (-1);
}
