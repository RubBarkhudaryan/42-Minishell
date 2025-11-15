/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 14:16:22 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/15 19:30:45 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expander.h"

int	match_question_or_char(const char **p, const char **s)
{
	if (**p == '?' || **p == **s)
	{
		(*p)++;
		(*s)++;
		return (1);
	}
	return (0);
}

int	match_star(const char **p, const char **s, const char **star,
		const char **ss)
{
	if (**p == '*')
	{
		*star = *p;
		(*p)++;
		*ss = *s;
		return (1);
	}
	return (0);
}

int	backtrack_star(const char **p, const char **s, const char **star,
		const char **ss)
{
	if (*star)
	{
		*p = *star + 1;
		(*ss)++;
		*s = *ss;
		return (1);
	}
	return (0);
}

char	*join_filenames(char *str1, char *str2, char delim)
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
	join = (char *)malloc(ft_strlen(str1) + ft_strlen(str2) + 2);
	if (!join)
		return (NULL);
	i = -1;
	j = -1;
	while (str1[++i])
		join[i] = str1[i];
	join[i++] = delim;
	while (str2[++j])
		join[i + j] = str2[j];
	join[i + j] = '\0';
	return (join);
}
