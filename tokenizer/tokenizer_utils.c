/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:10:31 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/07/23 18:49:16 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	ft_isalpha(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int	ft_inset(char c, char *set)
{
	int	i;

	if (!set)
		return (0);
	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		++i;
	}
	return (0);
}

int	ft_strcmp(char *str1, char *str2)
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

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

char	*ft_substr(char *str, unsigned int start, size_t len)
{
	char	*substr;
	size_t	strlen;
	size_t	i;

	i = 0;
	strlen = ft_strlen(str);
	if (start > strlen)
		return (ft_strdup(""));
	if (len > strlen - start)
		len = strlen - start;
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	while (i < len && str[start + i])
	{
		substr[i] = str[start + i];
		++i;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*res;

	i = 0;
	res = (char *)malloc(ft_strlen(str) + 1);
	while (i < ft_strlen(str))
	{
		res[i] = str[i];
		++i;
	}
	res[i] = '\0';
	return (res);
}
