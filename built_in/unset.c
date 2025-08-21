/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:17:49 by apatvaka          #+#    #+#             */
/*   Updated: 2025/08/21 22:06:40 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bulit_in.h"

int	ft_unset(char **args, t_env **env)
{
	int	i;

	i = 0;
	while (args[++i])
		remove_env_node(env, args[i]);
	return (0);
}
