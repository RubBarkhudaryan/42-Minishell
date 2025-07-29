/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:21:23 by apatvaka          #+#    #+#             */
/*   Updated: 2025/07/28 19:01:28 by apatvaka         ###   ########.fr       */
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

t_env	*env_new_node(char *key, char *value)
{
	t_env	*tmp;

	tmp = malloc(sizeof(t_env));
	if (!tmp)
		return (NULL);
	if (!value || !*value)
		tmp->flag = 1;
	else
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
	if (!new || !*env)
		return (1);
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}
