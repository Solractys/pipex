/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:04:00 by csilva-s          #+#    #+#             */
/*   Updated: 2025/08/15 19:09:13 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strrchr(const char *s, int c);

char	*ft_strrchr(const char *s, int c)
{
	short	i;
	char	cc;
	char	*result;

	i = 0;
	cc = (char )c;
	result = NULL;
	if (!cc)
		return ((char *)s + ft_strlen(s));
	while (s[i])
	{
		if (s[i] == cc)
			result = (char *)&s[i];
		i++;
	}
	if (c == 0)
		result = (char *)&s[i];
	return (result);
}
