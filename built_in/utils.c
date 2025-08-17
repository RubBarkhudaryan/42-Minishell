/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:42:35 by apatvaka          #+#    #+#             */
/*   Updated: 2025/08/17 17:49:41 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	print_helper(char *arg, char *error_msg)
{
	if (printf("%s", arg) < 0)
	{
		perror(error_msg);
		return (1);
	}
	return (0);
}
