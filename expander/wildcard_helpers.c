/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 19:25:43 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/15 15:16:55 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expander.h"

void	free_wildcard_tools(t_file *files, DIR *dir, t_expand *exp)
{
	t_file	*temp;

	while (files)
	{
		temp = files;
		files = files->next;
		free(temp->filename);
		free(temp);
	}
	closedir(dir);
	free(exp->res);
	free(exp->tk);
}

char	*get_filename(char *wildcard)
{
	int		i;

	if (!wildcard)
		return (NULL);
	i = 0;
	while (wildcard[i])
	{
		if (wildcard[i] == '.')
			break ;
		++i;
	}
	return (ft_substr(wildcard, 0, i));
}

char	*get_extension(char *wildcard)
{
	int		i;

	if (!wildcard)
		return (NULL);
	i = 0;
	while (wildcard[i])
	{
		if (wildcard[i] == '.')
			break ;
		++i;
	}
	if (!wildcard[i])
		return (NULL);
	return (ft_substr(wildcard, i + 1, ft_strlen(wildcard) - i));
}

char	*make_wildcard(char *source)
{
	int			i;
	int			asterisk;
	t_expand	wild;

	wild.res = ft_strdup("");
	asterisk = 0;
	i = 0;
	while (source[i])
	{
		if (source[i] == '*' && !asterisk)
		{
			append_star(&wild);
			asterisk = 1;
			while (source[i] && source[i] == '*')
				i++;
		}
		else
		{
			append_char(&wild, source[i]);
			asterisk = 0;
			i++;
		}
	}
	return (wild.res);
}

int	wildcard_match(const char *pattern, const char *str)
{
	const char	*star;
	const char	*ss;

	star = NULL;
	ss = str;
	if (!str)
		return (0);
	while (*str)
	{
		if (match_question_or_char(&pattern, &str))
			continue ;
		if (match_star(&pattern, &str, &star, &ss))
			continue ;
		if (backtrack_star(&pattern, &str, &star, &ss))
			continue ;
		return (0);
	}
	while (*pattern == '*')
		pattern++;
	return (*pattern == '\0');
}
