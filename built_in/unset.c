/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<<< HEAD:tokenizer/parse_subshell.c
/*   parse_subshell.c                                   :+:      :+:    :+:   */
========
/*   unset.c                                            :+:      :+:    :+:   */
>>>>>>>> execute:built_in/unset.c
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<<< HEAD:tokenizer/parse_subshell.c
/*   Created: 2025/08/06 14:49:19 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/08/15 20:48:32 by rbarkhud         ###   ########.fr       */
========
/*   Created: 2025/08/10 13:17:49 by apatvaka          #+#    #+#             */
/*   Updated: 2025/08/11 18:52:16 by apatvaka         ###   ########.fr       */
>>>>>>>> execute:built_in/unset.c
/*                                                                            */
/* ************************************************************************** */

#include "bulit_in.h"

<<<<<<<< HEAD:tokenizer/parse_subshell.c
int	parse_subshell(t_token **head, char *str, int i)
{
	int	l_count;
	int	r_count;
	int	is_alpha;
	int	new_i;

	l_count = 0;
	r_count = 0;
	is_alpha = 0;
	while (str[i])
	{
		if (str[i] == '(')
		{
			add_token(head, ft_substr(str, i, 1));
			++i;
			++l_count;
		}
		else if (str[i] == ')')
		{
			while (str[i] && str[i] == ')')
			{
				++i;
				++r_count;
			}
			add_token(head, ft_substr((const char *)str, i - r_count, r_count));
		}
		else
			++i;
	}
	if (l_count == r_count && is_alpha)
		return (i);
	return (-1);
========
int	ft_unset(char **args, t_env **env)
{
	int	i;

	i = 0;
	while (args[++i])
		remove_env_node(env, args[i]);
	return (0);
>>>>>>>> execute:built_in/unset.c
}
