/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 22:45:36 by csilva-s          #+#    #+#             */
/*   Updated: 2025/09/18 20:08:20 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*gnl_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s);
		i++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*s3;
	size_t	i;
	size_t	size;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	j = 0;
	size = gnl_strlen(s1) + gnl_strlen(s2);
	s3 = malloc((size + 1) * sizeof(char));
	if (!s3)
		return (NULL);
	while (i < size - gnl_strlen(s2))
	{
		s3[i] = s1[i];
		i++;
	}
	while (i < size)
		s3[i++] = s2[j++];
	s3[i] = '\0';
	return (s3);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = gnl_strlen(s);
	if (start >= slen)
		return (NULL);
	if (len > slen - start)
		len = slen - start;
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
