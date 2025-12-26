/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:53:11 by csilva-s          #+#    #+#             */
/*   Updated: 2025/12/25 23:13:53 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	check_path(char *str)
{
	int i = 0;
	char *path = "PATH=";
	int len = ft_strlen(path);
	int same = 0;
	while(str[i] && i <= len)
	{
		if (str[i] == path[i])
			same++;
		i++;
	}
	if (same == len)
		return (1);
	else
		return (0);
}
char	**find_path(char **envp)
{
	char **path = NULL;
	int i = 0;
	while (envp[i] != NULL)
	{
		if (check_path(envp[i]))
		{
			path = ft_split(envp[i], ':');
			char *path_line = path[0];
			path[0] = &path_line[5];
			break ;
		}
		i++;
	}
	return (path);
}
void	ft_print_path(char **path)
{
	int i = 0;
	while (path[i])
		ft_printf("%s\n", path[i++]);
}

int	find_correct_path(char **path, char *command)
{
	int	result;

	result = 0;
	while (path[result] != NULL)
	{
		char *pathname = ft_strjoin(path[result], "/");
		ft_printf("%s\n", ft_strjoin(pathname, command));
		if (access(ft_strjoin(pathname, command), X_OK) == 0)
			return (result);
		result++;
	}
	return (-1);
}

void	execute_command(char *pathname, char **command, char **envp)
{
	char *valid_path = ft_strjoin(pathname, "/");
	execve(ft_strjoin(valid_path, command[0]), command, envp);
}
void	check_inputs(char **argv)
{
	if (argv[1][0] == '\0')
	{
		write (2, "error", 5);
		exit(0);
	}
	else if (argv[2][0] == '\0')
	{
		write (2, "error", 5);
		exit(0);
	}
	else if (argv[3][0] == '\0')
	{
		write (2, "error", 5);
		exit(0);
	}
	else if (argv[4][0] == '\0')
	{
		write (2, "error", 5 );
		exit(0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		return (0);
	check_inputs(argv);
	int	fd[2];
	int infile = open(argv[1], O_RDONLY);
	int	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (infile < 0 || outfile < 0)
		return (0);
	// parser
	char **cmd1 = NULL;
	char **cmd2 = NULL;
	cmd1 = ft_split(argv[2], ' ');
	cmd2 = ft_split(argv[3], ' ');
	char **path = find_path(envp);
	int line1 = find_correct_path(path, cmd1[0]);
	if (line1 < 0)
	{
		ft_printf("this file don't exits");
		return (0);
	}
	int line2 = find_correct_path(path, cmd2[0]);
	if (line2 < 0)
	{
		ft_printf("this file don't exits");
		return (0);
	}
	// connection
	pipe(fd);
	// 1 child
	if (fork() == 0)
	{
		dup2(infile, 0);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		close(infile);
		close(outfile);
		execute_command(path[line1], cmd1, envp);
		exit(0);
	}
	// 2 child
	if (fork() == 0)
	{
		dup2(outfile, 1);
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		close(infile);
		close(outfile);
		execute_command(path[line2], cmd2, envp);
		exit(0);
	}
	close(fd[0]);
	close(fd[1]);
	close(infile);
	close(outfile);
	wait(NULL);
	wait(NULL);
	return (0);
}
