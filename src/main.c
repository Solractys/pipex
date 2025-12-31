/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:53:11 by csilva-s          #+#    #+#             */
/*   Updated: 2025/12/30 00:42:46 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_info	init_pipex(char **av, char **envp)
{
	t_info	pipex;

	pipex.infile = open(av[1], O_RDONLY);
	pipex.outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex.infile < 0 || pipex.outfile < 0)
	{
		close(pipex.infile);
		close(pipex.outfile);
		perror("file");
		exit (EXIT_FAILURE);
	}
	pipex.cmd1 = ft_split(av[2], ' ');
	pipex.cmd2 = ft_split(av[3], ' ');
	pipex.path = ft_split(find_path(envp), ':');
	if (!pipex.path || !pipex.cmd1 || !pipex.cmd2)
	{
		free_pipex(pipex);
		perror("command error");
		exit (1);
	}
	pipex.line1 = find_line(pipex.path, pipex.cmd1[0]);
	pipex.line2 = find_line(pipex.path, pipex.cmd2[0]);
	return (pipex);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_info	pipex;
// 	int		fd[2];
// 	int		pid;
// 	int		pid2;
//
// 	if (argc != 5)
// 		return (0);
// 	pipex = init_pipex(argv, envp);
// 	pipe(fd);
// 	pid = fork();
// 	if (pid == 0)
// 		execute_routine(pipex, fd, 1, envp);
// 	close(fd[1]);
// 	pid2 = fork();
// 	if (pid2 == 0)
// 		execute_routine(pipex, fd, 2, envp);
// 	close(fd[0]);
// 	free_pipex(pipex);
// 	wait(NULL);
// 	wait(NULL);
// 	return (0);
// }
int	main(int ac, char **av, char **envp)
{
	int	fd[2];
	int	cmd_count;
	int	init_cmd;
	int	infile;
	int	outfile;
	int	i;
	int	pid;
	int	old_fd;

	if (ac < 5)
		return (0);
	infile = open(av[1], O_RDONLY);
	outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	cmd_count = ac - 3;
	init_cmd = 2;
	old_fd = -1;
	i = 0;
	while (i < cmd_count)
	{
		char	**current_cmd = ft_split(av[init_cmd + i], ' ');
		ft_printf("%s", current_cmd[0]);
		if (i < cmd_count - 1)
			pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			if (old_fd == -1)
				old_fd = infile;
			else
				dup2(old_fd, STDIN_FILENO);
			if (i == cmd_count - 1)
				dup2(outfile, STDOUT_FILENO);
			else
				dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			close(infile);
			close(outfile);
			char	**path = ft_split(find_path(envp), ':');
			char	*cmd_path = find_line(path, current_cmd[0]);
			if (!cmd_path)
			{
				perror("command not found");
				exit(1);
			}
			execve(cmd_path, current_cmd, envp);
			perror("failed");
			exit(1);
		}
		close(fd[1]);
		close(old_fd);
		old_fd = fd[0];
		i++;
	}
	while(i-- > 0)
	{
		ft_printf("o caraio");
		wait(NULL);
	}
	close(infile);
	close(outfile);
	close(fd[0]);
	close(fd[1]);
}
