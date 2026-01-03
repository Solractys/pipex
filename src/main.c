/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:53:11 by csilva-s          #+#    #+#             */
/*   Updated: 2026/01/03 20:10:19 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	check_here_doc(char **av)
{
	int		pipe_here_doc[2];
	char	*limiter;
	char	*line;

	if (ft_strncmp(av[1], "here_doc", 9) != 0)
		return (open(av[1], O_RDONLY));
	pipe(pipe_here_doc);
	limiter = ft_strjoin(av[2], "\n");
	while (1)
	{
		line = get_next_line(0);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, pipe_here_doc[1]);
		free(line);
	}
	free(limiter);
	close(pipe_here_doc[1]);
	return (pipe_here_doc[0]);
}

int	main(int ac,char **av, char **envp)
{
	int	fd[2];
	int	cmd_count;
	int	init_cmd;
	int	infile;
	int	outfile;
	int	i;
	int	old_fd;
	int	pid;

	if (ac < 5)
		return (0);
	infile = check_here_doc(av);
	outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (infile == -1 || outfile == -1)
	{
		perror("Error opening file");
		return (1);
	}
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		cmd_count = ac - 4;
		init_cmd = 3;
	}
	else
	{
		cmd_count = ac - 3;
		init_cmd = 2;
	}
	old_fd = -1;
	i = 0;
	while (i < cmd_count)
	{
		char	**current_cmd = ft_split(av[init_cmd + i], ' ');
		if (i < cmd_count - 1)
			pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
				dup2(infile, STDIN_FILENO);
			else
				dup2(old_fd, STDIN_FILENO);
			if (i == cmd_count - 1)
				dup2(outfile, STDOUT_FILENO);
			else
				dup2(fd[1], STDOUT_FILENO);
			if (i < cmd_count - 1)
			{
				close(fd[0]);
				close(fd[1]);
			}
			if (i > 0)
				close(old_fd);
			close(infile);
			close(outfile);
			char	**path = ft_split(find_path(envp), ':');
			char	*cmd_path = find_line(path, current_cmd[0]);
			if (!cmd_path)
			{
				free_path(current_cmd);
				free(cmd_path);
				free_path(path);
				perror("command not found");
				exit(127);
			}
			free_path(path);
			execve(cmd_path, current_cmd, envp);
			perror("failed");
			exit(1);
		}
		if (i < cmd_count - 1)
			close(fd[1]);
		if (old_fd != -1)
			close (old_fd);
		if (i < cmd_count - 1)
			old_fd = fd[0];
		free_path(current_cmd);
		i++;
	}
	int	status;
	while(i-- > 0)
		wait(&status);
	close(infile);
	close(outfile);
	exit(WEXITSTATUS(status));
}
