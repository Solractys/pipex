/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 00:44:09 by csilva-s          #+#    #+#             */
/*   Updated: 2026/01/04 19:18:18 by csilva-s         ###   ########.fr       */
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
	int		fd[2];
	int		cmd_count;
	int		init_cmd;
	int		infile;
	int		outfile;
	int		old_fd;
	pid_t	*pid;
}	t_pipex;

void	execute_routine(char **current_cmd, char **envp);
void	free_pipex(t_pipex *pipex);

void	execute_command(char **envp, char **current_cmd);
char	*find_line(char **path, char *command);
char	*find_path(char	**envp);
void	free_path(char	**str);
void	redirect_and_close(int i, t_pipex pipex);
void	children_routine(t_pipex pipex, char **av, char **envp);
t_pipex	init_pipex(char **av, int ac);
#endif
