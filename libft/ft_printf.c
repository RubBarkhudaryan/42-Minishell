/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:39:10 by alen              #+#    #+#             */
/*   Updated: 2025/05/06 19:24:10 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_format(char format)
{
	if (format == 'd' || format == 'i' || format == 'x' || format == 'u'
		|| format == 'X' || format == 'c' || format == 's' || format == 'p'
		|| format == '%')
	{
		return (1);
	}
	return (0);
}

static int	orientate_params(char param, va_list args, int count)
{
	if (param == 'c')
		count += ft_putchar(va_arg(args, int));
	if (param == 's')
		count += ft_putstr(va_arg(args, char *));
	if (param == 'd' || param == 'i')
		count += ft_putnbr(va_arg(args, int), 0);
	if (param == 'p')
	{
		count += ft_putstr("0x");
		count += base_number("0123456789abcdef", (unsigned long)va_arg(args,
					void *));
	}
	if (param == 'x')
		count += base_number("0123456789abcdef", (unsigned int)va_arg(args,
					unsigned int));
	if (param == 'X')
		count += base_number("0123456789ABCDEF", (unsigned int)va_arg(args,
					unsigned int));
	if (param == 'u')
		count += base_number("0123456789", (unsigned int)va_arg(args,
					unsigned int));
	if (param == '%')
		count += ft_putchar('%');
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		ret;
	va_list	args;

	ret = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			if (check_format(*(format + 1)))
				ret += orientate_params(*(format + 1), args, 0);
			++format;
		}
		else
		{
			ft_putchar(*format);
			++ret;
		}
		++format;
	}
	va_end(args);
	return (ret);
}
