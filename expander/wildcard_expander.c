/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 19:23:41 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/15 19:28:07 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expander.h"

bool	create_node(t_file **list, char *filename)
{
	t_file	*new_node;
	t_file	*tmp;

	new_node = malloc(sizeof(t_file));
	if (!new_node)
		return (false);
	new_node->filename = ft_strdup(filename);
	new_node->next = NULL;
	if (!new_node->filename)
		return (free(new_node), false);
	if (*list == NULL)
		*list = new_node;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
	return (true);
}

t_file	*get_dir_struct(DIR *dir)
{
	struct dirent	*dirp;
	t_file			*head;

	head = NULL;
	while (1)
	{
		dirp = readdir(dir);
		if (!dirp)
			break ;
		if (!create_node(&head, dirp->d_name))
			return (perror("minishell"), closedir(dir), NULL);
	}
	return (head);
}

int	is_matching_with_wildcard(char *pattern, char *file, int show_hidden)
{
	char	*f_name;
	char	*f_ext;
	char	*p_name;
	char	*p_ext;
	int		status;

	if (!show_hidden && file[0] == '.')
		return (0);
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
	process_files(&file, files, set_show_hiddens(file.tk));
	if (ft_strcmp(file.res, "") == 0)
		res = ft_split(source, ' ');
	else
		res = ft_split(file.res, ' ');
	free_wildcard_tools(head, dir, &file);
	return (res);
}
