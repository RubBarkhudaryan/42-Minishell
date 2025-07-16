/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:05:59 by apatvaka          #+#    #+#             */
/*   Updated: 2025/01/30 17:06:02 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dest_ft;
	const unsigned char	*src_ft;

	i = 0;
	dest_ft = (unsigned char *)dest;
	src_ft = (const unsigned char *)src;
	if (dest_ft == NULL && src_ft == NULL)
		return (NULL);
	while (i < n)
	{
		dest_ft[i] = src_ft[i];
		++i;
	}
	return (dest_ft);
}
