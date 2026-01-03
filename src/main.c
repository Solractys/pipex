/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:53:11 by csilva-s          #+#    #+#             */
/*   Updated: 2026/01/02 21:56:32 by csilva-s         ###   ########.fr       */
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
	line = NULL;
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

t_pipex	init_pipex(char **av, int ac)
{
	t_pipex pipex;

	pipex.infile = check_here_doc(av);
	pipex.outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		pipex.init_cmd = 4;
		pipex.cmd_count = ac - 4;
	}
	else
	{
		pipex.init_cmd = 2;
		pipex.cmd_count = ac - 3;
	}
	pipex.old_fd = -1;
	return (pipex);
}

void	redirect_close(t_pipex pipex, int fd[2], int i)
{
	if (pipex.old_fd == -1)
		dup2(pipex.infile, STDIN_FILENO);
	else
		dup2(pipex.old_fd, STDIN_FILENO);
	if (i == pipex.cmd_count - 1)
		dup2(pipex.outfile, STDOUT_FILENO);
	else
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(pipex.infile);
	close(pipex.outfile);
}
void	execute_routine(char **current_cmd, char **envp)
{
		char	**path = ft_split(find_path(envp), ':');
		char	*cmd_path = find_line(path, current_cmd[0]);
		if (!cmd_path)
		{
			perror("command not found");
			exit(1);
		}
		free_path(path);
		execve(cmd_path, current_cmd, envp);
		perror("failed");
		exit(1);
}

// void	init_fds(int fd[2])
// {
// 	fd[0] = -1;
// 	fd[1] = -1;
// }

void	execute_commands(t_pipex pipex, char **av, char **envp)
{
	int	i;
	int	fd[2];
	char	**current_cmd;

	i = 0;
	while (i < pipex.cmd_count)
	{
	   	current_cmd = ft_split(av[pipex.init_cmd + i], ' ');
		if (i < pipex.cmd_count - 1)
			pipe(fd);
		if (fork() == 0)
		{
			redirect_close(pipex, fd, i);
			execute_routine(current_cmd, envp);
		}
		close(fd[1]);
		close(pipex.old_fd);
		pipex.old_fd = fd[0];
		free_path(current_cmd);
		i++;
	}
	close(pipex.old_fd);
	while(i-- > 0)
		wait(NULL);
	close(fd[1]);
	close(fd[0]);
}
int	main(int ac, char **av, char **envp)
{
	t_pipex pipex;

	if (ac < 5)
		return (0);
	pipex = init_pipex(av, ac);
	execute_commands(pipex, av, envp);
	close(pipex.infile);
	close(pipex.outfile);
	exit(0);
}
