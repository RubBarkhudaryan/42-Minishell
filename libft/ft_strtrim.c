/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:47:32 by apatvaka          #+#    #+#             */
/*   Updated: 2025/01/30 17:07:57 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *s2)
{
	size_t	start;
	size_t	end;

	if (!s1 || !*s1)
		return (ft_strdup(""));
	if (!s2 || !*s2)
		return (ft_strdup((char *)s1));
	end = ft_strlen(s1) - 1;
	start = 0;
	while (ft_strchr(s2, s1[start]) && start <= end)
		++start;
	if (start > end)
		return (ft_strdup(""));
	while (ft_strchr(s2, s1[end]) && end > 0)
		--end;
	return (ft_substr(s1, start, end - start + 1));
}
