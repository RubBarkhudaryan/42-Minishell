/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_maker_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 19:27:49 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/15 19:31:12 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expander.h"

int	set_show_hiddens(char *pattern)
{
	if (pattern[0] == '.')
		return (1);
	return (0);
}

void	append_match(t_expand *file, char *filename)
{
	file->piece = join_filenames(filename, file->res, ' ');
	free(file->res);
	file->res = ft_strdup(file->piece);
	free(file->piece);
}

void	process_files(t_expand *file, t_file *files, int show_hiddens)
{
	while (files)
	{
		if (is_matching_with_wildcard(file->tk, files->filename,
				show_hiddens))
			append_match(file, files->filename);
		files = files->next;
	}
}

void	append_char(t_expand *w, char c)
{
	char	*tmp;
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	tmp = w->res;
	w->res = ft_strjoin(tmp, str);
	free(tmp);
}

void	append_star(t_expand *w)
{
	char	*tmp;

	tmp = w->res;
	w->res = ft_strjoin(tmp, "*");
	free(tmp);
}
