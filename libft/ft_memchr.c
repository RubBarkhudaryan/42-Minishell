/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:34:42 by apatvaka          #+#    #+#             */
/*   Updated: 2025/01/30 17:05:42 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ret_s;
	size_t			i;

	i = 0;
	ret_s = (unsigned char *)s;
	while (i < n)
	{
		if (ret_s[i] == (unsigned char)c)
			return ((void *)s + i);
		++i;
	}
	return (NULL);
}
