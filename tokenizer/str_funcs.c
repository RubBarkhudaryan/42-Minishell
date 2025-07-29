/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:37:04 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/07/28 18:37:04 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./tokenizer.h"

char	*tk_substr(char *str, unsigned int start, size_t len)
{
	char	*substr;
	size_t	strlen;
	size_t	i;

	i = 0;
	strlen = tk_strlen(str);
	if (start > strlen)
		return (tk_strdup(""));
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

char	*tk_strdup(char *str)
{
	int		i;
	char	*res;

	i = 0;
	res = (char *)malloc(tk_strlen(str) + 1);
	while (i < tk_strlen(str))
	{
		res[i] = str[i];
		++i;
	}
	res[i] = '\0';
	return (res);
}
