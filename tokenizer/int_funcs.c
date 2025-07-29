/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:36:29 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/07/28 18:36:29 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./tokenizer.h"

int	tk_strcmp(char *str1, char *str2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str1[i] || str2[j])
	{
		if (str1[i] != str2[j])
			return (str1[i] - str2[j]);
		++i;
		++j;
	}
	return (0);
}

int	tk_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}
