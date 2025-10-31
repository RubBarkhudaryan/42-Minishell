/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:07:18 by apatvaka          #+#    #+#             */
/*   Updated: 2025/10/30 21:30:30 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bulit_in.h"

char	*is_append(char *args, int *len, int *flag)
{
	int	i;

	if (!args || !*args)
		return (*flag = -1, NULL);
	i = -1;
	if (ft_isdigit(args[0]) || args[0] == '=' || args[0] == '+')
		return (*flag = -1, NULL);
	while (args[++i])
		if (args[i] == '=' || args[i] == '+')
			break ;
	if (i && args[i] == '+' && args[i + 1] == '=')
		return (*len = i, *flag = 1, &args[i + 2]);
	if (i && args[i] == '=')
	{
		if (!ft_isalnum(args[i - 1]) && args[i - 1] != '_')
			return (*flag = -1, NULL);
		return (*len = i, *flag = 0, &args[i + 1]);
	}
	if (i == (int)ft_strlen(args))
	{
		if (!ft_isalnum(args[i - 1]) && args[i - 1] != '_')
			return (*flag = -1, NULL);
		return (*len = i, *flag = 2, args);
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
		*value = ft_strdup("");
		if (!*value)
			return (free(*key), perror("malloc failed\n"), -1);
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

int	add_or_replace_value(char *key, char *value, int flag, t_shell *shell)
{
	t_env	*node;
	char	*tmp;

	node = search_node(key, shell->env);
	if (!node)
		return (add_env_end(&(shell->env), key, value));
	free(key);
	if (!flag)
	{
		free(node->value);
		node->value = ft_strdup(value);
		if (!node->value)
			return (1);
		free(value);
	}
	else
	{
		tmp = ft_strjoin(node->value, value);
		if (!tmp)
			return (1);
		free(node->value);
		node->value = tmp;
		free(value);
	}
	return (node->flag = 0, 0);
}

int	ft_export(char **args, t_shell *shell)
{
	char	*key;
	char	*value;
	int		flag;
	int		i;

	key = NULL;
	value = NULL;
	if (!args || !*args)
		return (1);
	if (args_len(args) == 1)
		return (print_export(shell->env));
	i = 0;
	while (args[++i])
	{
		flag = get_assignment_type(args[i], &key, &value);
		if (flag == -1 || add_or_replace_value(key, value, flag, shell))
			return (free(value), free(key), 1);
	}
	return (0);
}
