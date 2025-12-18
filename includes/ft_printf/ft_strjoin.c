/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:10:00 by csilva-s          #+#    #+#             */
/*   Updated: 2025/08/15 19:09:13 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strjoin(char const *s1, char const *s2);

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	i;
	size_t	size;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	j = 0;
	size = ft_strlen(s1) + ft_strlen(s2);
	s3 = ft_calloc(size + 1, sizeof(char));
	if (!s3)
		return (NULL);
	while (i < size - ft_strlen(s2))
	{
		s3[i] = s1[i];
		i++;
	}
	while (i < size)
		s3[i++] = s2[j++];
	s3[i] = '\0';
	return (s3);
}
