/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:53:11 by csilva-s          #+#    #+#             */
/*   Updated: 2025/12/27 20:19:02 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	check_path(char *str)
{
	return (ft_strncmp(str, "PATH=", 5) == 0);
}
char	**find_path(char **envp)
{
	char **path;
	int		i;

	i = 0;
	path = NULL;
	while (envp[i] != NULL)
	{
		if (check_path(envp[i]))
		{
			path = ft_split(envp[i] + 5, ':');
			break ;
		}
		i++;
	}
	return (path);
}

char	*find_correct_path(char **path, char *command)
{
	int		result;
	char	*pathname;
	char	*pathname2;

	result = 0;
	while (path[result] != NULL)
	{
		pathname = ft_strjoin(path[result], "/");
		pathname2 = ft_strjoin(pathname, command);
		if (access(pathname2, X_OK) == 0)
		{
			free(pathname);
			return (pathname2);
		}
		free(pathname);
		free(pathname2);
		result++;
	}
	return (NULL);
}

void	free_path(char **path)
{
	int i;

	i = 0;
	if (!path)
		return ;
	while(path[i])
		free(path[i++]);
	free(path);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		return (0);
	int	fd[2];
	int infile;
	int	outfile;
	char **cmd1;
	char **cmd2;
	char **path;
	char	*line1;
	char	*line2;

	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		exit(1);
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
	{
		close(infile);
		exit(1);
	}
	cmd1 = ft_split(argv[2], ' ');
	cmd2 = ft_split(argv[3], ' ');
	path = find_path(envp);
	if (path == NULL)
	{
		free_path(cmd1);
		free_path(cmd2);
		ft_putstr_fd("Error to clone path", 2);
		exit(1);
	}
	line1 = find_correct_path(path, cmd1[0]);
	if (line1 == NULL)
	{
		ft_putstr_fd("this file don't exits", 2);
		free_path(path);
		free_path(cmd1);
		free_path(cmd2);
		close (infile);
		close (outfile);
		exit(1);
	}
	line2 = find_correct_path(path, cmd2[0]);
	if (line2 == NULL)
	{
		ft_putstr_fd("this file don't exits", 2);
		free_path(path);
		free(line1);
		free_path(cmd1);
		free_path(cmd2);
		close (infile);
		close (outfile);
		exit (1);
	}
	free_path(path);
	pipe(fd);
	if (fork() == 0)
	{
		dup2(infile, 0);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		close(infile);
		close(outfile);
		execve(line1, cmd1, envp);
		free(line1);
		free(line2);
		free_path(cmd1);
		free_path(cmd2);
		ft_putstr_fd("command 1 error", 2);
		exit(1);
	}
	if (fork() == 0)
	{
		dup2(outfile, 1);
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		close(infile);
		close(outfile);
		execve(line2, cmd2, envp);
		free(line1);
		free(line2);
		free_path(cmd1);
		free_path(cmd2);
		ft_putstr_fd("command 2 error", 2);
		exit(1);
	}
	free_path(cmd1);
	free_path(cmd2);
	free(line1);
	free(line2);
	close(fd[0]);
	close(fd[1]);
	close(infile);
	close(outfile);
	wait(NULL);
	wait(NULL);
	return (0);
}
