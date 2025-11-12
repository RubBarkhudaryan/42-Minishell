/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:24:36 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/13 03:37:51 by rbarkhud         ###   ########.fr       */
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
			while (token[i])
			{
				if (token[i] != '\\' && token[i + 1] == quote)
					break ;
				i++;
			}
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
			while (token[j])
			{
				if (token[j] != '\\' && token[j + 1] == quote)
					break ;
				j++;
			}
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

char	*join_args(char *str1, char *str2)
{
	int		i;
	int		j;
	char	*join;

	if (!str1 && str2)
		return (ft_strdup(str2));
	if (str1 && !str2)
		return (ft_strdup(str1));
	if (!str1 && !str2)
		return (NULL);
	join = (char *)malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!join)
		return (NULL);
	i = -1;
	j = -1;
	while (str1[++i])
		join[i] = str1[i];
	while (str2[++j])
		join[i + j] = str2[j];
	join[i + j] = '\0';
	return (join);
}
