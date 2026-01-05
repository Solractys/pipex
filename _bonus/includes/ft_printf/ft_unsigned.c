/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:52:27 by csilva-s          #+#    #+#             */
/*   Updated: 2025/08/15 19:43:57 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_unsigned(unsigned int nbr)
{
	unsigned int	num;

	num = (unsigned int)nbr;
	return (ft_putstr_fd(ft_itoa(num), 1));
}
