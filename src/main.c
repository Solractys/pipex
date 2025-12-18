/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:53:11 by csilva-s          #+#    #+#             */
/*   Updated: 2025/12/17 21:07:03 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../includes/ft_printf/ft_printf.h"

int	main(void)
{
	pid_t i = fork();
	if (i == 0)
	{
		ft_printf("hello from fork\n");
		exit (42);
	}
	else
	{
		int code;
		wait(&code);
		ft_printf("i wait the finish: %d", WEXITSTATUS(code));
	}
	return (0);
}
