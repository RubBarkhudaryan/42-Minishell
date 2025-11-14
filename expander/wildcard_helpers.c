/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 19:25:43 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/14 21:48:40 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expander.h"

void	free_wildcard_list(t_file *files)
{
	t_file	*temp;

	while (files)
	{
		temp = files;
		files = files->next;
		free(temp->filename);
		free(temp);
	}
}

char	*get_filename(char *wildcard)
{
	int		i;

	if (!wildcard)
		return (NULL);
	i = 0;
	while (wildcard[i])
	{
		if (wildcard[i] == '.')
			break ;
		++i;
	}
	return (ft_substr(wildcard, 0, i));
}

char	*get_extension(char *wildcard)
{
	int		i;

	if (!wildcard)
		return (NULL);
	i = 0;
	while (wildcard[i])
	{
		if (wildcard[i] == '.')
			break ;
		++i;
	}
	if (!wildcard[i])
		return (NULL);
	return (ft_substr(wildcard, i + 1, ft_strlen(wildcard) - i));
}
