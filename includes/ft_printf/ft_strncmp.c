/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:57:00 by csilva-s          #+#    #+#             */
/*   Updated: 2025/08/15 19:09:13 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n);

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				i;
	unsigned char	*target1;
	unsigned char	*target2;

	i = 0;
	target1 = (unsigned char *)s1;
	target2 = (unsigned char *)s2;
	while (target1[i] && target2[i] && n > 0)
	{
		if (target1[i] != target2[i])
			return (target1[i] - target2[i]);
		i++;
		n--;
	}
	if (n == 0)
		return (0);
	return (target1[i] - target2[i]);
}
