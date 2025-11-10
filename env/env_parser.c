/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:21:17 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/10 15:07:24 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_parser.h"

char	*create_env_string(t_env *node)
{
	char	*tmp;
	char	*result;

	if (!node->flag)
		tmp = ft_strjoin(node->key, "=");
	else
		tmp = ft_strdup(node->key);
	if (!tmp)
		return (NULL);
	if (node->flag == 0 && node->value == NULL)
		result = ft_strdup(tmp);
	else
		result = ft_strjoin(tmp, node->value);
	free(tmp);
	return (result);
}

char	**convert_envp_to_string(t_env *head)
{
	char	**ret;
	int		i;
	int		len;

	i = 0;
	len = env_list_size(head);
	if (!head || !len)
		return (NULL);
	ret = (char **)malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (NULL);
	while (head)
	{
		ret[i] = create_env_string(head);
		head = head->next;
		++i;
	}
	ret[i] = NULL;
	return (ret);
}

char	*get_value_from_env(t_env *head, char *key)
{
	t_env	*tmp;

	tmp = head;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

t_env	*create_env_node(char *env_str)
{
	t_env	*node;
	char	*equal_sign;
	char	*key;
	char	*value;

	equal_sign = ft_strchr(env_str, '=');
	if (!equal_sign)
	{
		key = ft_strdup(env_str);
		value = ft_strdup("");
	}
	else
	{
		key = ft_substr(env_str, 0, equal_sign - env_str);
		value = ft_strdup(equal_sign + 1);
	}
	if (!key || !value)
		return (NULL);
	node = env_new_node(key, value);
	if (!node)
	{
		free(key);
		free(value);
	}
	return (node);
}

t_env	*parse_environment(char **envp)
{
	t_env	*head;
	t_env	*current;
	int		i;

	head = NULL;
	i = -1;
	while (envp[++i])
	{
		if (!head)
		{
			head = create_env_node(envp[i]);
			if (!head)
				return (NULL);
			current = head;
		}
		else
		{
			current->next = create_env_node(envp[i]);
			if (!current->next)
				return (NULL);
			current = current->next;
		}
	}
	return (head);
}
