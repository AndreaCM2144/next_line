/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrcarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 18:40:03 by andrcarr          #+#    #+#             */
/*   Updated: 2026/08/04 14:50:28 by andrcarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_append_buffer(char *stash, const char *buffer)
{
	char	*joined;

	joined = ft_strjoin(stash, buffer);
	free(stash);
	return (joined);
}

static char	*ft_read_and_save(int fd, char *stash)
{
	char	*buffer;
	int		bytes_read;

	if (ft_strchr(stash, '\n'))
		return (stash);
	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (free(stash), NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), free(stash), NULL);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			stash = ft_append_buffer(stash, buffer);
			if (!stash)
				return (free(buffer), NULL);
		}
	}
	return (free(buffer), stash);
}

char	*ft_extract_line(char *stash)
{
	size_t	len;
	char	*result;

	if (!stash || !stash[0])
		return (NULL);
	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	result = ft_substr(stash, 0, len);
	return (result);
}

char	*ft_clean_stash(char *stash)
{
	size_t		start;
	char		*new;

	start = 0;
	while (stash[start] && stash[start] != '\n')
		start++;
	if (!stash[start] || !stash[start + 1])
	{
		free(stash);
		return (NULL);
	}
	new = ft_substr(stash, start + 1, ft_strlen(stash) - start - 1);
	free(stash);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = ft_read_and_save(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_extract_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = ft_clean_stash(stash);
	return (line);
}
