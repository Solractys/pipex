/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:41:35 by csilva-s          #+#    #+#             */
/*   Updated: 2025/08/15 19:43:03 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_cases(char c, va_list args)
{
	int		count;
	char	*nbr;

	count = 0;
	if (c == 'c')
		count += ft_putchar_fd(va_arg(args, int), 1);
	else if (c == 's')
		count += ft_putstr_fd(va_arg(args, char *), 1);
	else if (c == 'p')
		count += ft_pointer((unsigned long)va_arg(args, void *));
	else if (c == 'd' || c == 'i')
	{
		nbr = ft_itoa(va_arg(args, int));
		count += ft_putstr_fd(nbr, 1);
		free(nbr);
	}
	else if (c == 'u')
		count += ft_putnbr_u(va_arg(args, unsigned int));
	else if (c == 'x')
		count += ft_hex((unsigned int)va_arg(args, int), "0123456789abcdef");
	else if (c == 'X')
		count += ft_hex((unsigned int)va_arg(args, int), "0123456789ABCDEF");
	else if (c == '%')
		count += ft_putchar_fd('%', 1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		count;
	int		i;
	va_list	args;

	va_start(args, format);
	count = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			count += ft_check_cases(format[i + 1], args);
			i++;
		}
		else
			count += ft_putchar_fd(format[i], 1);
		i++;
	}
	va_end(args);
	return (count);
}
