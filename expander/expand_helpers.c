/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 22:49:15 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/09/12 22:49:15 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expander.h"

int	is_var_name_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

void	refresh_args_val(t_expand *exp, char *join, int *ind, int inc_by)
{
	exp->piece = join_args(exp->res, join);
	free(join);
	change_val(&exp->res, &exp->piece);
	*ind = *ind + inc_by;
}

void	add_val(t_expand *exp, int *i)
{
	if (exp->tk[*i] == '\\' && ft_inset(exp->tk[*i + 1], "\'\""))
		refresh_args_val(exp, ft_strdup((char [2]){exp->tk[*i + 1], '\0'}), i, 2);
	else
		refresh_args_val(exp, ft_strdup((char [2]){exp->tk[*i], '\0'}), i, 1);
}

void	change_val(char **str1, char **str2)
{
	free(*str1);
	*str1 = ft_strdup(*str2);
	free(*str2);
}

char	*join_args(char *str1, char *str2)
{
	int		i;
	int		j;
	char	*join;

	if (!str1 && str2)
		return (ft_strdup(str2));
	if (str1 && !str2)
		return (ft_strdup(str1));
	if (!str1 && !str2)
		return (NULL);
	join = (char *)malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!join)
		return (NULL);
	i = -1;
	j = -1;
	while (str1[++i])
		join[i] = str1[i];
	while (str2[++j])
		join[i + j] = str2[j];
	join[i + j] = '\0';
	return (join);
}
