/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:07:18 by apatvaka          #+#    #+#             */
/*   Updated: 2025/07/28 19:04:02 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bulit_in.h"

char	**env_to_export_string(t_env *head)
{
	char	**ret;
	char	*tmp_key;
	char	*tmp_value;
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
		tmp_key = ft_strjoin(head->key, "=\"");
		tmp_value = ft_strjoin(head->value, "\"");
		ret[i] = ft_strjoin(tmp_key, tmp_value);
		free(tmp_key);
		free(tmp_value);
		head = head->next;
		++i;
	}
	ret[i] = NULL;
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
	char	**env_string;
	int		i;

	env_string = env_to_export_string(env);
	if (!env_string)
		return (1);
	sort_string_array(env_string);
	i = -1;
	while (env_string[++i])
		printf("declare -x %s\n", env_string[i]);
	free_split(env_string);
	return (0);
}

char	*is_append(char *args, int *len, int *flag)
{
	int	i;

	i = -1;
	while (args[++i])
		if (!ft_isalpha(args[i]))
			break ;
	if (i && args[i] == '+' && args[i + 1] == '=')
		return (*len = i, *flag = 1, &args[i + 1]); // append flag
	if (i && args[i] == '=')
		return (*len = i, *flag = 0, &args[i]);
	if (i == (int)ft_strlen(args)) // no parameter
		return (*len = i, *flag = 2, args);
	return (*flag = -1, NULL);
}

int	get_assignment_type(char *args, char **key, char **value)
{
	int		flag;
	char	*args_value;
	int		key_len;
	int		value_len;

	args_value = is_append(args, &key_len, &flag);
	if (flag == -1)
		return (perror("export: not a valid identifier"), -1); // change
	if (flag == 0)
		value_len = ft_strlen(args) - key_len - 1;
	else if (flag == 1)
		value_len = ft_strlen(args) - key_len - 2;
	else
	{
		*key = ft_strdup(args);
		*value = ft_strdup("");
		return (flag);
	}
	*key = ft_substr(args, 0, key_len);
	*value = ft_substr(args, ft_strlen(args_value), value_len);
	return (flag);
}

int	add_or_replace_value(char *key, char *value, int flag, t_env *env)
{
	t_env	*node;
	char	*tmp;

	node = search_node(key, env);
	if (!node)
		return (add_env_end(&env, key, value), 0);
	free(key);
	if (!flag)
	{
		free(node->value);
		node->value = ft_strdup(value);
		free(value);
	}
	else
	{
		tmp = ft_strjoin(node->value, value);
		free(node->value);
		node->value = tmp;
		free(value);
	}
	return (0);
}

// {"export", "ls=la", "ls+=bbbbb", NULL}

int	ft_export(char **args, t_env *env)
{
	char	*key;
	char	*value;
	int		flag;
	int		i;

	key = NULL;
	value = NULL;
	if (!args || !*args)
		return (1);
	if (args_len(args) == 2) // {"export", NULL}
		print_export(env);
	i = 0;
	while (args[++i])
	{
		flag = get_assignment_type(args[i], &key, &value);
		if (flag != -1 && add_or_replace_value(key, value, flag, env))
			return (free(value), free(key), 1);
	}
	return (0);
}
