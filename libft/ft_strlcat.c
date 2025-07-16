/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:56:26 by apatvaka          #+#    #+#             */
/*   Updated: 2025/01/30 17:07:23 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(dst);
	j = 0;
	if (size == 0 || i >= size)
		return (size + ft_strlen(src));
	while (i + j < size - 1 && src[j])
	{
		dst[i + j] = src[j];
		++j;
	}
	dst[i + j] = '\0';
	return (i + ft_strlen(src));
}
