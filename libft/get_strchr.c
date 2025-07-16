/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_strchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:13:10 by apatvaka          #+#    #+#             */
/*   Updated: 2025/04/17 20:13:34 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_strchr(char *s, int c)
{
	char	*ret_s;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	ret_s = (char *)s;
	while (ret_s[i])
	{
		if (ret_s[i] == (char)c)
			return (&ret_s[i]);
		++i;
	}
	if (ret_s[i] == (char)c)
		return (&ret_s[i]);
	return (NULL);
}
