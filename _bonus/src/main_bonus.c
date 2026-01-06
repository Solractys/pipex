/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:53:11 by csilva-s          #+#    #+#             */
/*   Updated: 2026/01/06 10:32:47 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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
		ft_printf("> ");
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
	t_pipex	pipex;

	pipex.infile = check_here_doc(av);
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
		pipex.outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		pipex.outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	handle_error_fd(pipex.infile, pipex.outfile);
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		pipex.cmd_count = ac - 4;
		pipex.init_cmd = 3;
	}
	else
	{
		pipex.cmd_count = ac - 3;
		pipex.init_cmd = 2;
	}
	handle_error_cmd(pipex.cmd_count, pipex.init_cmd, av);
	pipex.old_fd = -1;
	pipex.pid = malloc(sizeof(pid_t) * pipex.cmd_count);
	return (pipex);
}

void	redirect_and_close(int i, t_pipex pipex)
{
	if (i == 0)
		dup2(pipex.infile, STDIN_FILENO);
	else
		dup2(pipex.old_fd, STDIN_FILENO);
	if (i == pipex.cmd_count - 1)
		dup2(pipex.outfile, STDOUT_FILENO);
	else
		dup2(pipex.fd[1], STDOUT_FILENO);
	if (i < pipex.cmd_count - 1)
	{
		close(pipex.fd[0]);
		close(pipex.fd[1]);
	}
	if (i > 0)
		close(pipex.old_fd);
	close(pipex.infile);
	close(pipex.outfile);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int		status;
	int		i;

	if (ac < 5)
		handle_error_msg("Usage: ./pipex infile cat 'wc -l' outfile", 1);
	pipex = init_pipex(av, ac);
	children_routine(pipex, av, envp);
	i = 0;
	while (i < pipex.cmd_count)
		waitpid(pipex.pid[i++], &status, 0);
	free(pipex.pid);
	close(pipex.infile);
	close(pipex.outfile);
	if (WEXITSTATUS(status))
		return (WEXITSTATUS(status));
	return (0);
}
