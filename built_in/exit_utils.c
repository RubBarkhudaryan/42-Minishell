/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 13:51:51 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/09 13:52:04 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bulit_in.h"

int	has_valid_sign_prefix(char *str, int *i)
{
	int	count;

	count = 0;
	while (str && str[*i] && (str[*i] == '-' || str[*i] == '+'))
	{
		count++;
		(*i)++;
	}
	if (count == 1)
		return (1);
	return (0);
}

int	is_valid_numeric_string(char *str)
{
	int	i;
	int	is_num;

	is_num = 0;
	i = 0;
	while (str && str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			if (is_num)
				return (0);
			if (!has_valid_sign_prefix(str, &i))
				return (0);
		}
		else
		{
			is_num = 1;
			i++;
		}
	}
	return (1);
}
