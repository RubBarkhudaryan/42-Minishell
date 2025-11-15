/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:24:36 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/15 18:59:29 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expander.h"

static void	init_split_elems(t_index *ind, char ***arr, int size, int init_val)
{
	ind->i = init_val;
	ind->j = init_val;
	ind->k = init_val;
	(*arr) = malloc(sizeof(char *) * size);
}

static int	loop_string(const char *string, int start, char quote)
{
	int	i;

	i = start;
	while (string[i] && string[i] != quote)
		++i;
	if (string[i])
		++i;
	return (i);
}

int	count_segments(const char *token)
{
	int	i;
	int	count;

	if (!token)
		return (0);
	i = 0;
	count = 0;
	while (token[i])
	{
		if (ft_inset(token[i], "\'\""))
		{
			i = loop_string(token, i + 1, token[i]);
			count++;
		}
		else
		{
			while (token[i] && !ft_inset(token[i], "\'\""))
				++i;
			count++;
		}
	}
	return (count);
}

char	**split_by_quotes(const char *token)
{
	char	**arr;
	t_index	ind;

	init_split_elems(&ind, &arr, count_segments(token) + 1, 0);
	if (!token || !arr)
		return (NULL);
	while (token[ind.i])
	{
		if (ft_inset(token[ind.i], "\'\""))
		{
			ind.j = loop_string(token, ind.i + 1, token[ind.i]);
			arr[ind.k++] = ft_substr(token, ind.i, (ind.j - ind.i));
			ind.i = ind.j;
		}
		else
		{
			ind.j = ind.i;
			while (token[ind.j] && !ft_inset(token[ind.j], "\'\""))
				++ind.j;
			arr[ind.k++] = ft_substr(token, ind.i, ind.j - ind.i);
			ind.i = ind.j;
		}
	}
	return (arr[ind.k] = NULL, arr);
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
