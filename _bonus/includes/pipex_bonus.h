/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 00:44:09 by csilva-s          #+#    #+#             */
/*   Updated: 2026/01/06 11:35:12 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "../ft_printf/ft_printf.h"
# include "gnl/get_next_line.h"

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

void	handle_error_msg(char *str, int error_code);
void	handle_error_fd(int infile, int outfile);
void	handle_error_cmd(int cmd_count, int init_cmd, char **av);
void	is_empty_cmd(char *str);

void	execute_command(char **envp, char **current_cmd);
char	*find_line(char **path, char *command);
char	*find_path(char	**envp);
void	redirect_and_close(int i, t_pipex pipex);
void	children_routine(t_pipex pipex, char **av, char **envp);

void	free_path(char	**str);
t_pipex	init_pipex(char **av, int ac);

#endif
