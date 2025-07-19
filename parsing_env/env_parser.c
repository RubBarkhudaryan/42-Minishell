/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:21:17 by apatvaka          #+#    #+#             */
/*   Updated: 2025/07/19 17:15:15 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_parser.h"

char	**convert_envp_to_string(t_env *head)
{
	char	**ret;
	t_env	*tmp_head;
	char	*tmp;
	int		i;
	int		len;

	i = 0;
	tmp_head = head;
	len = env_list_size(head);
	if (!tmp_head || !len)
		return (NULL); //??
	ret = (char **)malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (NULL);
	while (tmp_head)
	{
		tmp = ft_strjoin(tmp_head->key, "=");
		ret[i] = ft_strjoin(tmp, tmp_head->value);
		free(tmp);
		tmp_head = tmp_head->next;
		++i;
	}
	ret[i] = NULL;
	return (ret);
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
			head = new_node(key, value);
			if (!head)
				return (NULL); // make error int
			current = head;
		}
		else
		{
			current->next = new_node(key, value);
			if (!current->next)
				return (NULL); // make error print
			current = current->next;
		}
	}
	return (head);
}
