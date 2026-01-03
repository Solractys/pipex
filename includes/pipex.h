/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 00:44:09 by csilva-s          #+#    #+#             */
/*   Updated: 2026/01/03 20:10:19 by csilva-s         ###   ########.fr       */
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
# include "../gnl/get_next_line.h"

typedef struct s_pipex
{
	int	fd[2];
	int	cmd_count;
	int	init_cmd;
	int	infile;
	int	outfile;
	int	old_fd;
}	t_pipex;

char	*find_line(char **path, char *command);
char	*find_path(char	**envp);
void	execute_routine(char **current_cmd, char **envp);
void	execute_commands(t_pipex pipex, char **av, char **envp);
void	free_path(char	**str);
void	free_pipex(t_pipex *pipex);
void	redirect_close(t_pipex pipex, int fd[2], int i);
t_pipex	init_pipex(char **av, int ac);
#endif
