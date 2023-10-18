/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:34:43 by yothmani          #+#    #+#             */
/*   Updated: 2023/10/18 17:18:33 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	file_handler(int fd_p, char *file_path, bool in_out)
{
	int	fd;
	int	fd_1;
	int	fd_2;
	int	permission;

	permission = O_RDONLY;
	fd_1 = STDIN_FILENO;
	fd_2 = STDOUT_FILENO;
	if (!in_out)
	{
		permission = O_WRONLY | O_CREAT | O_TRUNC;
		fd_1 = STDOUT_FILENO;
		fd_2 = STDIN_FILENO;
	}
	fd = open(file_path, permission, 0777);
	if (fd == -1)
		fprintf(stderr, "error  file input not found");
	dup2(fd, fd_1);
	dup2(fd_p, fd_2);
	close(fd);
}

int	validation(int argc, char **argv)
{
	if (argc != 5)
		return (-1);
	if (access(argv[1], O_RDONLY) < 0)
		return (-2);
	if (access(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC) < 0)
		return (-3);
	return (0);
}

void	*extract_paths(char **envp)
{
 	char 	**paths_tab;
	char	*path;
	
	while (*envp && !ft_strnstr(*envp, "PATH=", 5))
		envp++;
	path = ft_substr(*envp, 5, ft_strlen(*envp) - 5);
	paths_tab = ft_split(path, ':');
	free(path);
	return(paths_tab);
}
