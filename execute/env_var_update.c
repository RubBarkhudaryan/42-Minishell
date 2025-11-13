/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 13:41:40 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/13 17:58:12 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	is_dollar(char *tmp)
{
	int	i;

	i = -1;
	while (tmp[++i])
		if (tmp[i] == '$')
			return (1);
	return (0);
}

void	shlvl_exec(t_shell *shell, int flag)
{
	int		shlvl;
	char	*level;
	char	*tmp;

	level = get_value_from_env(shell->env, "SHLVL");
	if (!level)
	{
		add_or_replace_value("SHLVL", "1", 0, shell);
		return ;
	}
	shlvl = ft_atoi(level);
	if (flag)
		tmp = ft_itoa(shlvl + 1);
	else
		tmp = ft_itoa(shlvl - 1);
	if (!tmp)
		return (perror("minishell"), (void)0);
	add_or_replace_value(ft_strdup("SHLVL"), ft_strdup(tmp), 0, shell);
	free(tmp);
}

void	update_env_var(t_ast *ast, t_shell *shell)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (ast->cmd && ast->cmd->args && ast->cmd->args[i])
	{
		tmp = ast->cmd->args[i];
		++i;
	}
	if (!tmp || !*tmp)
		return ;
	add_or_replace_value(ft_strdup("_"), ft_strdup(tmp), 0, shell);
}
