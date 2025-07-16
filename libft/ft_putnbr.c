/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:03:48 by apatvaka          #+#    #+#             */
/*   Updated: 2025/04/15 19:26:09 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	rec(int n)
{
	char	num;
	int		sum;

	sum = 0;
	num = (n % 10) + '0';
	if (n / 10 != 0)
	{
		n /= 10;
		sum += rec(n);
	}
	ft_putchar(num);
	++sum;
	return (sum);
}

int	ft_putnbr(int n, int sum)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		sum += 11;
		return (sum);
	}
	if (n == 0)
	{
		ft_putchar('0');
		sum += 1;
		return (sum);
	}
	if (n < 0)
	{
		ft_putchar('-');
		sum += 1;
		n *= -1;
	}
	return (sum + rec(n));
}
