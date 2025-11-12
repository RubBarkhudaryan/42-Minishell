/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:24:36 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/12 19:20:17 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expander.h"

int	count_segments(const char *token)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	while (token[i])
	{
		if (ft_inset(token[i], "\'\""))
		{
			quote = token[i++];
			while (token[i] && token[i] != quote)
				i++;
			if (token[i])
				i++;
			count++;
		}
		else
		{
			while (token[i] && !ft_inset(token[i], "\'\""))
				i++;
			count++;
		}
	}
	return (count);
}

char	**split_by_quotes(const char *token)
{
	char	**arr;
	int		i;
	int		j;
	int		k;
	char	quote;

	i = 0;
	k = 0;
	arr = malloc(sizeof(char *) * (count_segments(token) + 1));
	if (!arr)
		return (NULL);
	while (token[i])
	{
		if (ft_inset(token[i], "\'\""))
		{
			quote = token[i];
			j = i + 1;
			while (token[j] && token[j] != quote)
				j++;
			if (token[j])
				j++;
			arr[k++] = ft_substr(token, i, j - i);
			i = j;
		}
		else
		{
			j = i;
			while (token[j] && !ft_inset(token[j], "\'\""))
				j++;
			arr[k++] = ft_substr(token, i, j - i);
			i = j;
		}
	}
	arr[k] = NULL;
	return (arr);
}
