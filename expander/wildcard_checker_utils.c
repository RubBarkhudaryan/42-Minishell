/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_checker_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:07:49 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/15 21:56:32 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expander.h"

int	check_str(char *tmp)
{
	int	j;

	if (!tmp)
		return (0);
	j = -1;
	while (tmp[++j])
	{
		if (tmp[j] == '*')
			return (1);
	}
	return (0);
}

int	check_asterisk(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return (0);
	i = -1;
	while (cmd->args && cmd->args[++i])
	{
		if (check_str(cmd->args[i]))
			return (1);
	}
	return (0);
}

char	**join_split(char **join, char **tmp)
{
	char	**ret;
	int		i;
	int		j;

	j = 0;
	i = 0;
	ret = malloc(sizeof(char *) * (args_len(join) + args_len(tmp) + 1));
	if (!ret)
		return (perror("minishell"), NULL);
	while (join && join[i])
	{
		ret[i] = ft_strdup(join[i]);
		++i;
	}
	while (tmp && tmp[j])
	{
		ret[i + j] = ft_strdup(tmp[j]);
		++j;
	}
	ret[i + j] = NULL;
	return (ret);
}

char	**join_expand_wildcards(t_cmd *cmd, int *len)
{
	int		i;
	char	**tmp;
	char	**join;
	int		count;

	i = 0;
	count = 0;
	join = NULL;
	tmp = NULL;
	while (cmd->args && cmd->args[i])
	{
		if (ft_strchr(cmd->args[i], '*'))
		{
			tmp = expand_wildcard(cmd->args[i]);
			join = join_split(join, tmp);
			free_split(tmp);
			count++;
		}
		++i;
	}
	*len = i - count;
	return (join);
}

void	update_args(t_cmd *cmd, int len, char **expand_asterisks)
{
	char	**free_args;
	int		i;
	int		j;
	int		k;

	k = -1;
	j = 0;
	i = -1;
	free_args = cmd->args;
	cmd->args = malloc(sizeof(char *) * (len + args_len(expand_asterisks) + 1));
	if (!cmd->args)
		return (perror("minishell"), (void)0);
	while (free_args[++i])
		if (!check_str(free_args[i]))
			cmd->args[j++] = ft_strdup(free_args[i]);
	while (expand_asterisks[++k])
		cmd->args[j++] = ft_strdup(expand_asterisks[k]);
	cmd->args[j] = NULL;
	free(cmd->cmd_name);
	cmd->cmd_name = ft_strdup(cmd->args[0]);
	free_split(free_args);
}
