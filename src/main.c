/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:53:11 by csilva-s          #+#    #+#             */
/*   Updated: 2025/12/29 15:28:25 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <stdio.h>

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
char	*find_line(char **path, char *command)
{
	int		i;
	char	*cmd;
	char	*cmd_path;

	if (access(command, X_OK) == 0)
		return (command);
	i = 0;
	cmd = ft_strjoin("/", command);
	while (path[i] != NULL)
	{
		cmd_path = ft_strjoin(path[i], cmd);
		if (access(cmd_path, X_OK) == 0)	
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

char	*find_path(char	**envp)
{
	int	i;
	
	i = 0;
	while(envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}
void	execute_rutine(t_info pipex, int *fd, int child_nb, char **envp)
{
	if (child_nb == 1)
	{
		dup2(pipex.infile, 0);
		dup2(fd[1], 1);
	}
	else
	{
		dup2(pipex.outfile, 1);
		dup2(fd[0], 0);
	}
	close(fd[0]);
	close(fd[1]);
	close(pipex.infile);
	close(pipex.outfile);
	if (child_nb == 1)
		execve(pipex.line1, pipex.cmd1, envp);
	else
		execve(pipex.line2, pipex.cmd2, envp);
	perror("execve");
	exit (EXIT_FAILURE);
}
t_info	init_pipex(char **av, char **envp)
{
	t_info	pipex;
	
	pipex.infile = open(av[1], O_RDONLY);
	pipex.outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex.infile < 0)
	{	
		perror("infile");
		exit (EXIT_FAILURE);
	}
	pipex.cmd1 = ft_split(av[2], ' ');
	pipex.cmd2 = ft_split(av[3], ' ');
	pipex.path = ft_split(find_path(envp), ':');
	if (!pipex.path || !pipex.cmd1 || !pipex.cmd2)
	{
		free_path(pipex.path);
		free_path(pipex.cmd1);
		free_path(pipex.cmd2);
		return (pipex);
	}
	pipex.line1 = find_line(pipex.path, pipex.cmd1[0]);
	pipex.line2 = find_line(pipex.path, pipex.cmd2[0]);
	return (pipex);
}
int	main(int argc, char **argv, char **envp)
{
	t_info	pipex;
	int		fd[2];
	int		pid;
	int		pid2;
	
	if (argc != 5)
		return (0);
	pipex = init_pipex(argv, envp);
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		execute_rutine(pipex, fd, 1, envp);
	}
	close(fd[1]);
	pid2 = fork();
	if (pid2 == 0)
	{
		execute_rutine(pipex, fd, 2, envp);
	}
	close(fd[0]);
	close(fd[1]);
	close(pipex.infile);
	close(pipex.outfile);
	wait(NULL);
	wait(NULL);
	return (0);
}
