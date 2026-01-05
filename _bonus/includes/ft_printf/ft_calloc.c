/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:53:09 by csilva-s          #+#    #+#             */
/*   Updated: 2025/08/15 19:09:13 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_calloc(size_t nmemb, size_t size);

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char		*temp;
	void				*mem;
	size_t				i;

	if (nmemb == 0 || size == 0)
		return (malloc(1));
	if (size && nmemb > (size_t) - 1 / size)
		return (NULL);
	mem = malloc(nmemb * size);
	if (!mem)
		return (NULL);
	temp = (unsigned char *)mem;
	i = 0;
	while (i < nmemb * size)
		temp[i++] = 0;
	return (mem);
}
