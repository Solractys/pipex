/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 00:25:26 by csilva-s          #+#    #+#             */
/*   Updated: 2026/01/05 17:04:59 by csilva-s         ###   ########.fr       */
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
