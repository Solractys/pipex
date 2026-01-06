/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 00:25:26 by csilva-s          #+#    #+#             */
/*   Updated: 2026/01/06 11:40:53 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_path(char	**str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	free_pipex(t_info pipex)
{
	free_path(pipex.path);
	if (pipex.line1 != NULL)
		free(pipex.line1);
	if (pipex.line2 != NULL)
		free(pipex.line2);
	if (pipex.cmd1 != NULL)
		free_path(pipex.cmd1);
	if (pipex.cmd2 != NULL)
		free_path(pipex.cmd2);
	close(pipex.infile);
	close(pipex.outfile);
}

void	handle_error_msg(char *str, int error_code)
{
	ft_putendl_fd(str, 2);
	exit(error_code);
}

void	is_empty_cmd(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32 || str[i] == 12 || str[i] == 13 || str[i] == 14)
		i++;
	if ((int)ft_strlen(str) == i)
		handle_error_msg("Invalid command", 1);
}
