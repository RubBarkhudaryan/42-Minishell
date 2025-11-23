/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 22:28:03 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/17 16:43:06 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./execute.h"

int	get_exit_code(int status)
{
	if (WIFSIGNALED(status))
	{
		g_status = WTERMSIG(status);
		return (128 + WTERMSIG(status));
	}
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
