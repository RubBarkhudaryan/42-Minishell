/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:21:23 by apatvaka          #+#    #+#             */
/*   Updated: 2025/07/22 13:51:20 by apatvaka         ###   ########.fr       */
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
	tmp->flag = 0; // Default flag value
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

int	replace_env_value(char *key, char *value, t_env *head, int flag)
{
	if (!key || !value || !head)
		return (1);
	while (head)
	{
		if (ft_strcmp(head->key, key) == 0)
		{
			free(head->value);
			head->value = ft_strdup(value);
			if (!head->value)
				return (1);
			head->flag = flag;
			return (0);
		}
		head = head->next;
	}
	return (1);
}
