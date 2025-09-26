/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:07:18 by apatvaka          #+#    #+#             */
/*   Updated: 2025/09/27 01:20:15 by rbarkhud         ###   ########.fr       */
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
	/*append flag*/
	if (i && args[i] == '+' && args[i + 1] == '=')
		return (*len = i, *flag = 1, &args[i + 2]);
	if (i && args[i] == '=')
		return (*len = i, *flag = 0, &args[i + 1]);
	/*no parameter*/
	if (i == (int)ft_strlen(args))
		return (*len = i, *flag = 2, args);
	/*if (is_alpha(args[0]) == 0)*/
	return (*flag = -1, NULL);
}

int	get_assignment_type(char *args, char **key, char **value)
{
	int		flag;
	char	*args_value;
	int		key_len;

	args_value = is_append(args, &key_len, &flag);
	/* change */
	if (flag == -1)
		return (ft_putstr_fd("export: not a valid identifier\n", 2), -1);
	if (flag == 2)
	{
		*key = ft_strdup(args);
		if (!*key)
			return (perror("malloc failed"), -1);
		*value = ft_strdup("");
		if (!*value)
			return (free(*key), perror("malloc failed"), -1);
		return (flag);
	}
	*key = ft_substr(args, 0, key_len);
	if (!*key)
		return (-1);
	*value = ft_strdup(args_value);
	if (!*value)
		return (free(*key), perror("malloc failed"), -1);
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

/*{"export", "ls=la", "ls+=bbbbb", NULL}*/

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
	/* {"export", NULL}*/
	if (args_len(args) == 1)
		return (print_export(shell->env));
	i = 0;
	while (args[++i])
	{
		flag = get_assignment_type(args[i], &key, &value);
		printf("flag: %d\n", flag);
		if (flag != -1 && add_or_replace_value(key, value, flag, shell))
			return (free(value), free(key), 1);
	}
	return (0);
}
