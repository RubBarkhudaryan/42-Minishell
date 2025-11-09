/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:22:00 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/09 13:53:31 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bulit_in.h"

static char	*get_env_entry(t_env *node)
{
	char	*entry;
	char	*tmp_key;
	char	*tmp_value;

	if (node->flag || !node->value)
		return (ft_strdup(node->key));
	tmp_key = ft_strjoin(node->key, "=\"");
	if (!tmp_key)
		return (NULL);
	tmp_value = ft_strjoin(node->value, "\"");
	if (!tmp_value)
	{
		free(tmp_key);
		return (NULL);
	}
	entry = ft_strjoin(tmp_key, tmp_value);
	free(tmp_key);
	free(tmp_value);
	return (entry);
}

static int	populate_export_array(char **array, t_env *head)
{
	int		i;
	t_env	*current;

	i = 0;
	current = head;
	while (current)
	{
		array[i] = get_env_entry(current);
		if (!array[i])
		{
			while (i > 0)
				free(array[--i]);
			return (0);
		}
		i++;
		current = current->next;
	}
	array[i] = NULL;
	return (1);
}

char	**env_to_export_string(t_env *head)
{
	char	**ret;
	int		len;

	len = env_list_size(head);
	if (len == 0)
		return (NULL);
	ret = malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (NULL);
	if (!populate_export_array(ret, head))
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}

static void	sort_string_array(char **arr)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	while (arr[++i])
	{
		j = i;
		while (arr[++j])
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

int	print_export(t_env *env)
{
	char	*tmp;
	char	**env_string;
	int		i;

	env_string = env_to_export_string(env);
	if (!env_string)
		return (perror("minishell"), 1);
	sort_string_array(env_string);
	i = -1;
	while (env_string[++i])
	{
		tmp = ft_strjoin("declare -x ", env_string[i]);
		if (!tmp)
			return (free_split(env_string), perror("malloc failed"), 1);
		if (print_helper(tmp, "minishell: export: ") || print_helper("\n",
				"minishell: export: "))
			return (free(tmp), free_split(env_string), 1);
		free(tmp);
	}
	free_split(env_string);
	return (0);
}
