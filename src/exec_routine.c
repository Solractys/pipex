/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 00:26:25 by csilva-s          #+#    #+#             */
/*   Updated: 2026/01/05 16:51:15 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*find_line(char **path, char *command)
{
	int		i;
	char	*cmd;
	char	*cmd_path;

	if (access(command, F_OK | X_OK) == 0)
		return (command);
	if (command[0] == '/' && access(command, F_OK | X_OK) != 0)
		return (NULL);
	i = 0;
	cmd = ft_strjoin("/", command);
	while (path[i] != NULL)
	{
		cmd_path = ft_strjoin(path[i], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			free(cmd);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free(cmd);
	return (NULL);
}

char	*find_path(char	**envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

void	execute_routine(t_info pipex, int *fd, int child_nb, char **envp)
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
