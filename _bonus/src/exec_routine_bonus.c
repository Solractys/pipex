/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_routine_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 00:26:25 by csilva-s          #+#    #+#             */
/*   Updated: 2026/01/06 10:21:41 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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

void	execute_command(char **envp, char **current_cmd)
{
	char	**path;
	char	*cmd_path;

	path = ft_split(find_path(envp), ':');
	cmd_path = find_line(path, current_cmd[0]);
	if (!cmd_path)
	{
		free_path(current_cmd);
		free_path(path);
		free(cmd_path);
		perror("command not found");
		exit(127);
	}
	free_path(path);
	execve(cmd_path, current_cmd, envp);
	perror("failed");
	free(cmd_path);
	exit(1);
}

void	children_routine(t_pipex pipex, char **av, char **envp)
{
	int		i;
	char	**current_cmd;
	int		pid;

	i = -1;
	while (++i < pipex.cmd_count)
	{
		current_cmd = ft_split(av[pipex.init_cmd + i], ' ');
		if (i < pipex.cmd_count - 1)
			pipe(pipex.fd);
		pid = fork();
		if (pid == 0)
		{
			redirect_and_close(i, pipex);
			execute_command(envp, current_cmd);
		}
		pipex.pid[i] = pid;
		if (i < pipex.cmd_count - 1)
			close(pipex.fd[1]);
		if (pipex.old_fd != -1)
			close (pipex.old_fd);
		if (i < pipex.cmd_count - 1)
			pipex.old_fd = pipex.fd[0];
		free_path(current_cmd);
	}
}
