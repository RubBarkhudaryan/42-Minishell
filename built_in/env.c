/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 20:03:20 by apatvaka          #+#    #+#             */
/*   Updated: 2025/08/10 13:00:32 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bulit_in.h"

int	print_env_list(t_env *env_list)
{
	char	**env_string;
	t_env	*current;
	int		i;
	char	*line;

	env_string = convert_envp_to_string(env_list);
	if (!env_string || !*env_string)
		return (1);
	current = env_list;
	i = -1;
	while (env_string[++i])
	{
		if (!current->flag)
		{
			line = ft_strjoin(env_string[i], "\n");
			if (!line)
				return (perror("malloc failed"), free_split(env_string), 1);
			if (print_helper(line, "env: "))
				return (free(line), free_split(env_string), 1);
			free(line);
		}
		current = current->next;
	}
	free_split(env_string);
	return (0);
}

int	ft_env(char **args, t_env *env_list)
{
	if (args_len(args) > 1)
	{
		perror("env: too many arguments\n");
		return (1);
	}
	return (print_env_list(env_list));
}
