/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:53:11 by csilva-s          #+#    #+#             */
/*   Updated: 2026/01/06 09:02:11 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

void	handle_error_input(int ac, char **av)
{
	if (ac != 5)
	{
		handle_error_msg("Error: expected 6 args.\nUsage: ./pipex <infile> \
			 'cmd1' 'cmd2' <outfile>", 1);
	}
	if (av[2][0] == '\0')
		handle_error_msg("first command don't exist", 1);
	if (av[3][0] == '\0')
		handle_error_msg("second command doen't exist", 1);
}

t_info	init_pipex(int ac, char **av, char **envp)
{
	t_info	pipex;

	handle_error_input(ac, av);
	pipex.infile = open(av[1], O_RDONLY);
	pipex.outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	handle_error_fd(pipex.infile, pipex.outfile);
	pipex.cmd1 = ft_split(av[2], ' ');
	pipex.cmd2 = ft_split(av[3], ' ');
	pipex.path = ft_split(find_path(envp), ':');
	pipex.line1 = find_line(pipex.path, pipex.cmd1[0]);
	pipex.line2 = find_line(pipex.path, pipex.cmd2[0]);
	if (!pipex.line1 || !pipex.line2)
	{
		free_pipex(pipex);
		handle_error_msg("command not found", 127);
	}
	return (pipex);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	pipex;
	int		fd[2];
	int		pid[2];
	int		status;

	pipex = init_pipex(argc, argv, envp);
	pipe(fd);
	pid[0] = fork();
	if (pid[0] == 0)
		execute_routine(pipex, fd, 1, envp);
	close(fd[1]);
	pid[1] = fork();
	if (pid[1] == 0)
		execute_routine(pipex, fd, 2, envp);
	close(fd[0]);
	free_pipex(pipex);
	waitpid(pid[0], &status, 0);
	waitpid(pid[1], &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
