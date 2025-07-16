/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:47:38 by apatvaka          #+#    #+#             */
/*   Updated: 2025/01/30 17:08:01 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ret_str;
	size_t			i;

	i = 0;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	else if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	ret_str = (char *)malloc(len + 1);
	if (!ret_str)
		return (NULL);
	while (s[start + i] && i < len)
	{
		ret_str[i] = s[start + i];
		++i;
	}
	if (ret_str[i] != '\0')
		ret_str[i] = '\0';
	return (ret_str);
}
