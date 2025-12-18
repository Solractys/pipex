/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 18:04:00 by csilva-s          #+#    #+#             */
/*   Updated: 2025/08/15 19:09:13 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_memchr(const void *s, int c, size_t n);

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cpy_s;
	unsigned char	cpy_c;
	short			i;

	i = 0;
	cpy_c = (unsigned char )c;
	cpy_s = (unsigned char *)s;
	while (n > 0)
	{
		if (cpy_s[i] == cpy_c)
			return (&cpy_s[i]);
		n--;
		i++;
	}
	return (NULL);
}
