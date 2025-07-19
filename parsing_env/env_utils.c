/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:21:23 by apatvaka          #+#    #+#             */
/*   Updated: 2025/07/19 17:14:42 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_parser.h"

void	free_split(char **ret)
{
	int	i;

	i = -1;
	while (ret[++i])
	{
		free(ret[i]);
	}
	free(ret);
}

t_env	*new_node(char *key, char *value)
{
	t_env	*tmp;

	tmp = malloc(sizeof(t_env));
	if (!tmp)
		return (NULL);
	tmp->key = key;
	tmp->value = value;
	tmp->next = NULL;
	return (tmp);
}

void	free_env_list(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

int	env_list_size(t_env *head)
{
	t_env	*tmp;
	int		i;

	tmp = head;
	if (!tmp)
		return (0);
	i = 0;
	while (tmp)
	{
		++i;
		tmp = tmp->next;
	}
	return (i);
}
