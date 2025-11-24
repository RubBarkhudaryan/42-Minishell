/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:55:35 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/24 15:40:31 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast.h"

t_token	*find_matching_parenthesis(t_token *start, int *ret_count)
{
	int		count;
	t_token	*current;
	int		flag;

	flag = 0;
	count = 0;
	current = start;
	while (current != NULL)
	{
		if (current->type == TK_L_PARENTHESIS)
			count++;
		else if (current->type == TK_R_PARENTHESIS)
		{
			if (!flag)
			{
				*ret_count = count;
				flag = 1;
			}
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
	while (current && is_valid_token_type(current->type))
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	throw_error(char *target)
{
	ft_putstr_fd(ERR_MSG, 2);
	ft_putstr_fd(target, 2);
	ft_putstr_fd("'\n", 2);
}


