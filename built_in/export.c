/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:07:18 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/15 19:05:22 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bulit_in.h"

char	*is_append(char *a, int *len, int *flag)
{
	int	i;

	if (!a || !*a)
		return (*flag = -1, NULL);
	i = -1;
	if (ft_isdigit(a[0]) || a[0] == '=' || a[0] == '+')
		return (*flag = -1, NULL);
	while (a[++i])
		if (a[i] == '=' || a[i] == '+' || (!ft_isalnum(a[i]) && a[i] != '_'))
			break ;
	if (i && a[i] == '+' && a[i + 1] == '=')
		return (*len = i, *flag = 1, &a[i + 2]);
	if (i && a[i] == '=')
	{
		if (!ft_isalnum(a[i - 1]) && a[i - 1] != '_')
			return (*flag = -1, NULL);
		return (*len = i, *flag = 0, &a[i + 1]);
	}
	if (i == (int)ft_strlen(a))
	{
		if (!ft_isalnum(a[i - 1]))
			return (*flag = -1, NULL);
		return (*len = i, *flag = 2, a);
	}
	return (*flag = -1, NULL);
}

int	get_assignment_type(char *args, char **key, char **value)
{
	int		flag;
	char	*args_value;
	int		key_len;

	args_value = is_append(args, &key_len, &flag);
	if (flag == -1)
		return (ft_putstr_fd("export: not a valid identifier\n", 2), -1);
	if (flag == 2)
	{
		*key = ft_strdup(args);
		if (!*key)
			return (perror("malloc failed\n"), -1);
		*value = NULL;
		return (flag);
	}
	*key = ft_substr(args, 0, key_len);
	if (!*key)
		return (-1);
	*value = ft_strdup(args_value);
	if (!*value)
		return (free(*key), perror("malloc failed\n"), -1);
	return (flag);
}

static int	handle_existing_node(t_env *node, char *value, int flag)
{
	char	*tmp;

	if (!flag)
	{
		if (node->value)
			free(node->value);
		if (value)
			node->value = ft_strdup(value);
		free(value);
	}
	else if (flag != 2)
	{
		tmp = ft_strjoin(node->value, value);
		if (!tmp)
			return (1);
		free(node->value);
		node->value = tmp;
		free(value);
	}
	else
		return (node->value = NULL, node->flag = 1, 0);
	return (node->flag = 0, 0);
}

int	add_or_replace_value(char *key, char *value, int flag, t_shell *shell)
{
	t_env	*node;

	node = search_node(key, shell->env);
	if (!node)
		return (add_env_end(&(shell->env), key, value));
	free(key);
	return (handle_existing_node(node, value, flag));
}

int	ft_export(char **args, t_shell *shell)
{
	char	*key;
	char	*value;
	int		flag;
	int		i;

	if (!args || !*args)
		return (1);
	key = NULL;
	value = NULL;
	if (args_len(args) == 1)
		return (print_export(shell->env));
	i = 0;
	while (args[++i])
	{
		flag = get_assignment_type(args[i], &key, &value);
		if (flag == -1 || add_or_replace_value(key, value, flag, shell))
		{
			if (value)
				free(value);
			if (key)
				free(key);
			return (1);
		}
	}
	return (0);
}
