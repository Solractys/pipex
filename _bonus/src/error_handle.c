/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 09:15:46 by csilva-s          #+#    #+#             */
/*   Updated: 2026/01/06 10:27:23 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	handle_error_msg(char *str, int error_code)
{
	ft_putendl_fd(str, 2);
	exit(error_code);
}

void	handle_error_cmd(int cmd_count, int init_cmd, char **av)
{
	int	i;

	i = 0;
	while (i <= cmd_count)
	{
		if (av[init_cmd + i][0] == '\0')
			handle_error_msg("Invalid commands", 1);
		i++;
	}
}

void	handle_error_fd(int infile, int outfile)
{
	if (infile < 0)
	{
		perror("infile");
		close(infile);
		close(outfile);
		exit(1);
	}
	if (outfile < 0)
	{
		perror("outfile");
		close(infile);
		close(outfile);
		exit(1);
	}
}
