/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrcarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 16:21:11 by andrcarr          #+#    #+#             */
/*   Updated: 2026/08/01 19:38:13 by andrcarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *str, int c)
{
	size_t	index;

	if (!str)
		return (NULL);
	index = 0;
	while (str[index])
	{
		if (str[index] == (char)c)
			return ((char *)&str[index]);
		index++;
	}
	if ((char)c == '\0')
		return ((char *)&str[index]);
	return (NULL);
}

char	*ft_strjoin(const char *first, const char *second)
{
	char	*joined;
	size_t	first_len;
	size_t	index;

	first_len = ft_strlen(first);
	joined = malloc(first_len + ft_strlen(second) + 1);
	if (!joined)
		return (NULL);
	index = 0;
	while (first && first[index])
	{
		joined[index] = first[index];
		index++;
	}
	while (second && *second)
		joined[index++] = *second++;
	joined[index] = '\0';
	return (joined);
}

char	*ft_substr(const char *str, size_t start, size_t len)
{
	char	*substring;
	size_t	str_len;
	size_t	index;

	if (!str)
		return (NULL);
	str_len = ft_strlen(str);
	if (start >= str_len)
		len = 0;
	else if (len > str_len - start)
		len = str_len - start;
	substring = malloc(len + 1);
	if (!substring)
		return (NULL);
	index = 0;
	while (index < len)
	{
		substring[index] = str[start + index];
		index++;
	}
	substring[index] = '\0';
	return (substring);
}
