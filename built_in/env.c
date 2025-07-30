/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 20:03:20 by apatvaka          #+#    #+#             */
/*   Updated: 2025/07/24 13:46:01 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bulit_in.h"

int	ft_env(char **args, t_env *env_list)
{
	char	**env_string;
	int		i;
	t_env	*tmp;

	tmp = env_list;
	if (args_len(args) > 1 && args_len(args))
	{
		perror("env: too many arguments\n");
		return (1);
	}
	env_string = convert_envp_to_string(env_list);
	if (!env_string || !*env_string)
		return (1);
	i = -1;
	while (env_string[++i])
	{
		if (!tmp->flag)
			printf("%s\n", env_string[i]);
		tmp = tmp->next;
	}
	free_split(env_string);
	return (0);
}
