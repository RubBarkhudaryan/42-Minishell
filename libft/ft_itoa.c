/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:46:14 by apatvaka          #+#    #+#             */
/*   Updated: 2025/01/30 17:04:23 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len_int(int n)
{
	int	ret_len;

	ret_len = 0;
	if (n < 0)
		++ret_len;
	while (n != 0)
	{
		++ret_len;
		n /= 10;
	}
	return (ret_len);
}

static int	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	else
		return (n);
}

char	*ft_itoa(int n)
{
	int		len_int;
	char	*ret_str;

	len_int = ft_len_int(n);
	if (n == 0)
		return (ft_strdup("0"));
	ret_str = (char *)malloc(len_int + 1);
	if (!ret_str)
		return (NULL);
	ret_str[len_int] = '\0';
	--len_int;
	while (len_int >= 0)
	{
		ret_str[len_int] = ft_abs(n % 10) + '0';
		if (n < 0 && n >= -9 && len_int == 1)
		{
			ret_str[0] = '-';
			len_int--;
		}
		n /= 10;
		--len_int;
	}
	return (ret_str);
}
