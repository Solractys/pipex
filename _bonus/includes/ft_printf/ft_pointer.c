/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 18:37:09 by csilva-s          #+#    #+#             */
/*   Updated: 2025/08/15 19:09:13 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pointer(unsigned long n)
{
	int	count;

	count = 0;
	if (!n)
		return (ft_putstr_fd("(nil)", 1));
	count += ft_putstr_fd("0x", 1);
	count += ft_hex(n, "0123456789abcdef");
	return (count);
}
