/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_nuber.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:15:31 by alen              #+#    #+#             */
/*   Updated: 2025/04/06 17:15:30 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "libft.h"

int	base_number(char *base, unsigned long num)
{
	int	count;

	count = 0;
	if (num >= ft_strlen(base))
		count += base_number(base, num / ft_strlen(base));
	ft_putchar(base[num % ft_strlen(base)]);
	count++;
	return (count);
}
