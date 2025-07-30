/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:07:18 by apatvaka          #+#    #+#             */
/*   Updated: 2025/07/30 20:17:33 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bulit_in.h"

char	*is_append(char *args, int *len, int *flag)
{
	int	i;

	i = -1;
	while (args[++i])
		if (!ft_isalpha(args[i]))
			break ;
	if (i && args[i] == '+' && args[i + 1] == '=')
		return (*len = i, *flag = 1, &args[i + 2]); // append flag
	if (i && args[i] == '=')
		return (*len = i, *flag = 0, &args[i + 1]);
	if (i == (int)ft_strlen(args)) // no parameter
		return (*len = i, *flag = 2, args);
	return (*flag = -1, NULL);
}

int	get_assignment_type(char *args, char **key, char **value)
{
	int		flag;
	char	*args_value;
	int		key_len;

	args_value = is_append(args, &key_len, &flag);
	if (flag == -1)
		return (perror("export: not a valid identifier"), -1); // change
	if (flag == 2)
	{
		*key = ft_strdup(args);
		*value = ft_strdup("");
		return (flag);
	}
	*key = ft_substr(args, 0, key_len);
	*value = ft_strdup(args_value);
	if (!*value)
		return (perror("malloc failed"), -1);
	return (flag);
}

int	add_or_replace_value(char *key, char *value, int flag, t_env *env)
{
	t_env	*node;
	char	*tmp;

	node = search_node(key, env);
	if (!node)
		return (add_env_end(&env, key, value));
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
	if (args_len(args) == 1) // {"export", NULL}
		print_export(env);
	i = 0;
	while (args[++i])
	{
		flag = get_assignment_type(args[i], &key, &value);
		if (flag != -1 && add_or_replace_value(key, value, flag, env))
			return (free(value), free(key), 1);
		// free(value);
		// free(key);
	}
	return (0);
}
