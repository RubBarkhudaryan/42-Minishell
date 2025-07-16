/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:49:51 by apatvaka          #+#    #+#             */
/*   Updated: 2025/05/03 22:30:18 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*get_line(int fd, char *line)
{
	char	*buf;
	int		read_size;

	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	read_size = 1;
	while (!get_strchr(line, '\n') && read_size > 0)
	{
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size == 0)
		{
			free(buf);
			return (line);
		}
		if (read_size < 0)
			return (free(buf), free(line), NULL);
		buf[read_size] = '\0';
		line = gnl_strjoin(line, buf);
	}
	free(buf);
	return (line);
}

static	char	*ft_clean_line(char *line)
{
	int		i;
	char	*str;

	i = 0;
	while (line[i] && line[i] != '\n')
		++i;
	if (line[i] == '\n')
		str = (char *)malloc(i + 2);
	else
		str = (char *)malloc(i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		str[i] = line[i];
		++i;
	}
	if (line[i] == '\n')
	{
		str[i] = line[i];
		++i;
	}
	str[i] = '\0';
	return (str);
}

char	*new_get_next_line(char *line)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = ft_strlen(line);
	while (line[i] && line[i] != '\n')
		++i;
	if (i == len || (line[i] == '\n' && line[i + 1] == '\0'))
		return (free(line), NULL);
	str = (char *)malloc(len - i);
	if (!str)
		return (free(line), NULL);
	len = i + 1;
	i = 0;
	while (line[len + i])
	{
		str[i] = line[len + i];
		++i;
	}
	str[i] = '\0';
	return (free(line), str);
}

char	*get_next_line(int fd)
{
	char		*clean_line;
	static char	*line;

	if (fd < 0 || BUFFER_SIZE == 0)
		return (free(line), NULL);
	line = get_line(fd, line);
	if (!line)
		return (NULL);
	clean_line = ft_clean_line(line);
	line = new_get_next_line(line);
	return (clean_line);
}
