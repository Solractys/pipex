/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:53:11 by csilva-s          #+#    #+#             */
/*   Updated: 2025/12/24 22:40:17 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

//  COMAND EXP:./pipex infile "ls -l" "wc -l" outfile

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

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		return (0);
	int	fd[2];
	int infile = open(argv[1], O_RDONLY);
	int	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (infile < 0 || outfile < 0)
		return (0);
	// parser
	char **cmd1 = NULL;
	char **cmd2 = NULL;
	cmd1 = ft_split(argv[1], ' ');
	cmd2 = ft_split(argv[4], ' ');
	char **path = find_path(envp);
	ft_print_path(path);
	char *command = ft_strjoin( "/usr/bin/", cmd1[0]);
	char *command2 = ft_strjoin( "/usr/bin/", cmd2[0]);
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
		execve(command, cmd1, envp);
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
		execve(command2, cmd2, envp);
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
