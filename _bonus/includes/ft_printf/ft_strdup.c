/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:19:00 by csilva-s          #+#    #+#             */
/*   Updated: 2025/08/15 19:07:48 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strdup(const char *s1);

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*s2;

	size = ft_strlen(s1) + 1;
	s2 = malloc(sizeof(char) * size);
	if (s2)
	{
		ft_strlcpy(s2, s1, size);
		return ((char *)s2);
	}
	return (NULL);
}
