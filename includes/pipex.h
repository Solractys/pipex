/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 00:44:09 by csilva-s          #+#    #+#             */
/*   Updated: 2026/01/06 08:35:57 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "../ft_printf/ft_printf.h"

typedef struct s_info
{
	char	*line1;
	char	*line2;
	char	**cmd1;
	char	**cmd2;
	char	**path;
	int		infile;
	int		outfile;
	pid_t	pid[2];
}	t_info;

char	*find_line(char **path, char *command);
char	*find_path(char	**envp);
void	execute_routine(t_info pipex, int *fd, int child_nb, char **envp);
void	free_path(char	**str);
void	free_pipex(t_info pipex);
void	handle_error_fd(int infile, int outfile);
void	handle_error_msg(char *str, int error_code);
#endif
