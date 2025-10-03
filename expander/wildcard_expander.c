/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 19:23:41 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/09/30 19:23:41 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expander.h"

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
	int		i;

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

	dir = opendir(".");
	res = ft_strdup("");
	if (!dir)
		return (perror("minishell"), free(res), NULL);
	if (ft_strcmp(wildcard, "*") == 0 || ft_strcmp(wildcard, "*.*") == 0)
	{
		dirp = readdir(dir);
		while (dirp)
		{
			char	*tmp;
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
	return res;
}

int main()
{
	char	*res;

	res = expand_wildcard("*");
	printf("files: %s\n", res);
	free(res);
	return (0);
}
