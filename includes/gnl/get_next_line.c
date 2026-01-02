/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 22:37:26 by csilva-s          #+#    #+#             */
/*   Updated: 2025/09/18 20:16:20 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_to_stash(int fd, char *stash, char *buffer)
{
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while (!gnl_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(stash);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = gnl_strjoin(stash, buffer);
		if (!temp)
		{
			free(stash);
			return (NULL);
		}
		free(stash);
		stash = temp;
	}
	return (stash);
}

char	*update_stash(char *stash, int line_size)
{
	char	*new_stash;
	int		i;

	i = 0;
	if (!stash[line_size])
	{
		free(stash);
		return (NULL);
	}
	new_stash = malloc((gnl_strlen(stash) - line_size + 1) * sizeof(char));
	if (!new_stash)
	{
		free(stash);
		return (NULL);
	}
	while (stash[line_size + i])
	{
		new_stash[i] = stash[line_size + i];
		i++;
	}
	new_stash[i] = '\0';
	free(stash);
	return (new_stash);
}

char	*extract_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	if (stash[i] == 0)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	stash = read_to_stash(fd, stash, buffer);
	free(buffer);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	if (line != NULL)
		stash = update_stash(stash, gnl_strlen(line));
	return (line);
}
