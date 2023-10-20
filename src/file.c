/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:34:43 by yothmani          #+#    #+#             */
/*   Updated: 2023/10/20 01:10:02 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	file_handler(int *fd_p, char *file_path, bool in_out)
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
	fd = open(file_path, permission);
	if (fd < 0)
		error("error  file input not found");
	dup2(fd, fd_1);
	dup2(fd_p[fd_2], fd_2);
	close(fd_p[fd_1]);
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

char	**extract_paths(char **envp)
{
	char	**paths_tab;
	char	*path;

	while (*envp && !ft_strnstr(*envp, "PATH=", 5))
		envp++;
	path = ft_substr(*envp, 5, ft_strlen(*envp) - 5);
	paths_tab = ft_split(path, ':');
	free(path);
	return (paths_tab);
}

char	*get_cmd_path(char **paths, char *cmd)
{
	char	*cmd_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(cmd_path, cmd);
		if (access(cmd_path, F_OK) == 0)
		{
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	i = 0;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (NULL);
}

bool	execute_cmd(char **paths, char *cmd, char **envp)
{
	char	**tmp;
	char	*cmd_path;

	tmp = ft_split(cmd, ' ');
	cmd_path = get_cmd_path(paths, tmp[0]);
	if (!cmd_path)
		return (false);
	return (execve(cmd_path, tmp, envp) >= 0);
}
