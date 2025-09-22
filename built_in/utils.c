/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:42:35 by apatvaka          #+#    #+#             */
/*   Updated: 2025/09/22 15:48:05 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bulit_in.h"

int	print_helper(char *arg, char *error_msg)
{
	if (printf("%s", arg) < 0 && error_msg)
	{
		perror(error_msg);
		return (1);
	}
	return (0);
}
