/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:53:11 by csilva-s          #+#    #+#             */
/*   Updated: 2025/12/18 21:02:16 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../includes/ft_printf/ft_printf.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		return (0);
	int	fd[2];
	int infile = open(argv[1], O_RDONLY);
	int	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	char *cmd1[] = {"wqa", NULL};
	char *cmd2[] = {"-w", NULL};

	pipe(fd);
	if (fork() == 0)
	{
		dup2(infile, 0);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		close(infile);
		execve("/usr/bin/grep", cmd1, envp);
		exit(0);
	}
	if (fork() == 0)
	{
		dup2(outfile, 1);
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		execve("/bin/wc", cmd2, envp);
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
