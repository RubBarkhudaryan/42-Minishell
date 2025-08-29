/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:42:35 by apatvaka          #+#    #+#             */
/*   Updated: 2025/08/26 14:26:58 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bulit_in.h"

int	print_helper(char *arg, char *error_msg)
{
	// if (!arg || !error_msg)
		// return (0);
	if (printf("%s", arg) < 0)
	{
		perror(error_msg);
		return (1);
	}
	return (0);
}
