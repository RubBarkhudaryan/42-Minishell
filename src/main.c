/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:31:32 by apatvaka          #+#    #+#             */
/*   Updated: 2025/07/14 16:54:32 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*line;

	while (true)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		tokenized(line);
		free(line);
	}
	return (0);
}
