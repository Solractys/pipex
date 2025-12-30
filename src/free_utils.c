/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 00:25:26 by csilva-s          #+#    #+#             */
/*   Updated: 2025/12/30 00:26:02 by csilva-s         ###   ########.fr       */
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
	free_path(pipex.cmd1);
	free_path(pipex.cmd2);
	free_path(pipex.path);
	free(pipex.line1);
	free(pipex.line2);
	close(pipex.infile);
	close(pipex.outfile);
}
