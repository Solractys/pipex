/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:07:07 by csilva-s          #+#    #+#             */
/*   Updated: 2025/08/15 19:33:26 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_itoa(int n);
static char	*ft_alok(int len);
static int	count_int(int n);

static int	count_int(int n)
{
	int	i;
	int	no_sign;

	i = 0;
	no_sign = 0;
	if (n < 0)
	{
		no_sign = -n;
		i++;
	}
	else
		no_sign = n;
	while ((no_sign / 10) != 0)
	{
		i++;
		no_sign = no_sign / 10;
	}
	return (i + 1);
}

static char	*ft_alok(int len)
{
	char	*result;

	if (len == 0)
		return (NULL);
	result = ft_calloc(sizeof(char), len + 1);
	if (!result)
		return (NULL);
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;
	long	nb;
	int		count;

	nb = n;
	count = count_int(nb);
	result = ft_alok(count);
	if (!result)
		return (NULL);
	if (nb < 0)
		nb = -nb;
	while (count > 0)
	{
		if (nb <= 9)
		{
			result[count - 1] = nb + 48;
			break ;
		}
		result[count - 1] = (nb % 10) + 48;
		nb /= 10;
		count--;
	}
	if (n < 0)
		result[0] = '-';
	return (result);
}
