#ifndef PIPEX_H
# define PIPEX_H

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "../includes/ft_printf/ft_printf.h"


typedef struct
{
	char	*line1;
	char	*line2;
	char	**cmd1;
	char	**cmd2;
	char	**path;
	int		infile;
	int		outfile;
}	t_info;

# endif
