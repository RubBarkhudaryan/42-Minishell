/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 19:23:41 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/14 21:59:34 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expander.h"

t_file	*get_dir_struct(DIR *dir)
{
	struct dirent	*dirp;
	t_file			*list;
	t_file			*head;
	t_file			*new;

	// t_file			*tmp;
	list = NULL;
	head = NULL;
	while (1)
	{
		dirp = readdir(dir);
		if (!dirp)
			break ;
		new = malloc(sizeof(t_file));
		if (!new)
			return (perror("minishell"), closedir(dir), NULL);
		new->filename = ft_strdup(dirp->d_name);
		new->next = NULL;
		if (!new->filename)
			return (perror("minishell"), free(new), closedir(dir), NULL);
		if (!head)
			head = new;
		else
			list->next = new;
		list = new;
	}
	// tmp = head;
	// while (tmp)
	// {
	// 	printf("thim = [%s]\n", tmp->filename);
	// 	tmp = tmp->next;
	// }
	return (head);
}

char	*make_wildcard(char *source)
{
	int			i;
	bool		asteriks;
	t_expand	wildcard;

	if (!source)
		return (ft_strdup(""));
	wildcard.res = ft_strdup("");
	asteriks = 0;
	i = 0;
	while (source[i])
	{
		if (source[i] == '*' && !asteriks)
		{
			wildcard.tk = ft_strdup(wildcard.res);
			free(wildcard.res);
			wildcard.res = ft_strjoin(wildcard.tk, "*");
			free(wildcard.tk);
			asteriks = 1;
			while (source[i] && source[i] == '*')
				++i;
		}
		else
		{
			if (!source[i])
				break ;
			wildcard.tk = ft_strdup(wildcard.res);
			free(wildcard.res);
			wildcard.piece = ft_substr(source, i, 1);
			wildcard.res = ft_strjoin(wildcard.tk, wildcard.piece);
			free(wildcard.tk);
			free(wildcard.piece);
			asteriks = 0;
			++i;
		}
	}
	return (wildcard.res);
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
		if (*pattern == '?' || *pattern == *str)
		{
			pattern++;
			str++;
			continue ;
		}
		if (*pattern == '*')
		{
			star = pattern++;
			ss = str;
			continue ;
		}
		if (star)
		{
			pattern = star + 1;
			str = ++ss;
			continue ;
		}
		return (0);
	}
	while (*pattern == '*')
		pattern++;
	return (*pattern == 0);
}

int	is_matching_with_wildcard(char *pattern, char *file)
{
	char	*f_name;
	char	*f_ext;
	char	*p_name;
	char	*p_ext;
	int		status;

	f_name = get_filename(file);
	f_ext = get_extension(file);
	p_name = get_filename(pattern);
	p_ext = get_extension(pattern);
	if (!p_ext)
		status = wildcard_match(p_name, f_name);
	else
		status = wildcard_match(p_name, f_name) && wildcard_match(p_ext, f_ext);
	free(f_name);
	free(f_ext);
	free(p_name);
	free(p_ext);
	return (status);
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

char	**expand_wildcard(char *source)
{
	t_expand	file;
	t_file		*files;
	t_file		*head;
	DIR			*dir;
	char		**res;

	dir = opendir(".");
	if (!dir)
		return (NULL);
	file.res = ft_strdup("");
	file.tk = make_wildcard(source);
	files = get_dir_struct(dir);
	head = files;
	while (files)
	{
		if (is_matching_with_wildcard(file.tk, files->filename))
		{
			file.piece = join_filenames(files->filename, file.res, ' ');
			free(file.res);
			file.res = ft_strdup(file.piece);
			free(file.piece);
		}
		files = files->next;
	}
	res = ft_split(file.res, ' ');
	free_wildcard_list(head);
	return (free(file.res), free(file.tk), closedir(dir), res);
}
