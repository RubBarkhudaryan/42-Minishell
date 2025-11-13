/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 19:23:41 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/13 19:52:51 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expander.h"

t_file	*get_dir_struct(DIR *dir)
{
	struct dirent	*dirp;
	t_file			*list;
	t_file			*head;
	t_file			*new;

	list = NULL;
	head = NULL;
	while(1)
	{
		dirp = readdir(dir);
		if (!dirp)
			break ;
		new = malloc(sizeof(t_file));
		if (!new)
			return (perror("minishell"), closedir(dir), NULL);
		new->filename = ft_strdup(dirp->d_name);
		if (!new->filename)
			return (perror("minishell"), free(new), closedir(dir), NULL);
		if(!head)
			head = new;
		else
			list->next = new;
		list = new;
	}
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

int	is_matching_with_wildcard(char *wildcard, char *file)
{
	char	*f_filename;
	char	*f_extension;
	char	*w_filename;
	char	*w_extension;
	int		i;
	int		j;

	f_filename = get_filename(file);
	f_extension = get_extension(file);
	w_filename = get_filename(wildcard);
	w_extension = get_filename(wildcard);
	if (!f_filename || !f_extension || !w_filename || w_extension)
		return (0);
	
}

int	main(void)
{
	t_file	*files;
	DIR		*dir;


	dir = opendir(".");

	files = get_dir_struct(dir);
	while (files)
	{
		printf("filename: %s\n", files->filename);
		files = files->next;
	}

	char	*wildcard = make_wildcard("***************......c***r**t**jhello*");

	printf("WILDCARD %s\n", wildcard);
	printf("FILENAME %s\n", get_filename(wildcard));
	printf("EXTENSION %s\n", get_extension(wildcard));

	return (0);
}

/*

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

char	*get_file_extension(char *wildcard)
{
	int	i;

	if (!wildcard)
		return (NULL);
	i = 0;
	while (wildcard[i] && wildcard[i] != '.')
		++i;
	if (wildcard[i] == '.')
		++i;
	return (ft_substr(wildcard, i, ft_strlen(wildcard + i)));
}

char	*expand_wildcard(char *wildcard)
{
	char			*res;
	DIR				*dir;
	struct dirent	*dirp;
	char			*extension;
	char			*tmp;

	dir = opendir(".");
	res = ft_strdup("");
	if (!dir)
		return (perror("minishell"), free(res), NULL);
	if (ft_strcmp(wildcard, "*") == 0 || ft_strcmp(wildcard, "*.*") == 0)
	{
		dirp = readdir(dir);
		while (dirp)
		{
			if (ft_strcmp(dirp->d_name, ".") && ft_strcmp(dirp->d_name, ".."))
			{
				tmp = join_filenames(res, dirp->d_name, ' ');
				free(res);
				res = tmp;
			}
			dirp = readdir(dir);
		}
	}
	else
	{
		extension = get_file_extension(wildcard);
		if (!extension)
			return (perror("minishell : file extension not found"), NULL);
		if (ft_strcmp(extension, "*") == 0)
		{
		}
		else
		{
		}
	}
	closedir(dir);
	return (res);
}
*/