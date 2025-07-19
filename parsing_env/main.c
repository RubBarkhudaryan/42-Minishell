/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:32:51 by apatvaka          #+#    #+#             */
/*   Updated: 2025/07/19 16:49:12 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_parser.h"

int	main(int argc, char **argv, char **env)
{
	t_env	*head;
	int		i;
	char	**this;

	(void)argc;
	(void)argv;
	head = parse_environment(env);
	this = convert_envp_to_string(head);
	i = -1;
	while (this[++i])
	{
		printf("%s\n", this[i]);
	}
	free_split(this);
	free_env_list(head);
}
