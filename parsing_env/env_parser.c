/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:21:17 by apatvaka          #+#    #+#             */
/*   Updated: 2025/07/25 18:12:48 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_parser.h"

char	**convert_envp_to_string(t_env *head)
{
	char	**ret;
	char	*tmp;
	int		i;
	int		len;

	i = 0;
	len = env_list_size(head);
	if (!head || !len)
		return (NULL); //??
	ret = (char **)malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (NULL);
	while (head)
	{
		tmp = ft_strjoin(head->key, "=");
		ret[i] = ft_strjoin(tmp, head->value);
		free(tmp);
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

t_env	*parse_environment(char **envp)
{
	int		i;
	t_env	*head;
	t_env	*current;
	char	*key;
	char	*value;
	char	*equal_sign;

	i = -1;
	head = NULL;
	while (envp[++i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (!equal_sign)
		{
			key = ft_strdup(envp[i]);
			value = ft_strdup("");
		}
		else
		{
			key = ft_substr(envp[i], 0, equal_sign - envp[i]);
			value = ft_strdup(equal_sign + 1);
		}
		if (!head)
		{
			head = env_new_node(key, value);
			if (!head)
				return (NULL); // make error int
			current = head;
		}
		else
		{
			current->next = env_new_node(key, value);
			if (!current->next)
				return (NULL); // make error print
			current = current->next;
		}
	}
	return (head);
}
