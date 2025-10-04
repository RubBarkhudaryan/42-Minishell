/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:21:23 by apatvaka          #+#    #+#             */
/*   Updated: 2025/10/03 20:14:41 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_parser.h"

t_env	*search_node(char *key, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	replace_env_value(char *key, char *value, t_env *head)
{
	int	flag;

	flag = 0;
	if (!value)
		flag = 1;
	if (!key || !head)
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

int	add_env_end(t_env **env, char *key, char *value)
{
	t_env	*tmp;
	t_env	*new;

	new = env_new_node(key, value);
	if (!new)
		return (1);
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}

void	remove_env_node(t_env **head, char *key)
{
	t_env	*current;
	t_env	*tmp;

	current = *head;
	if (!current)
		return ;
	if (ft_strcmp(current->key, key) == 0)
	{
		*head = current->next;
		free(current->key);
		free(current->value);
		free(current);
		return ;
	}
	while (current->next)
	{
		if (ft_strcmp(current->next->key, key) == 0)
		{
			tmp = current->next;
			current->next = tmp->next;
			free(tmp->key);
			return (free(tmp->value), free(tmp), (void)0);
		}
		current = current->next;
	}
}
