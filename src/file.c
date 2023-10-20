/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:34:43 by yothmani          #+#    #+#             */
/*   Updated: 2023/10/20 18:58:35 by yothmani         ###   ########.fr       */
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
		permission = O_RDWR | O_CREAT | O_TRUNC;
		fd_1 = STDOUT_FILENO;
		fd_2 = STDIN_FILENO;
	}
	fd = open(file_path, permission, 0777);
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
	return (0);
}
// if (access(argv[4], O_RDWR | O_CREAT | O_TRUNC) < 0)
// 	return (-3);

char	**extract_paths(char **envp)
{
	char	**paths_tab;
	char	*path;

	while (*envp && !ft_strnstr(*envp, "PATH=", 5))
		envp++;
	path = ft_substr(*envp, 5, ft_strlen(*envp) - 5);
	paths_tab = ft_split(path, ':');
	free(path);
	path = NULL;
	return (paths_tab);
}

// char	*get_cmd_path(char **paths, char *cmd)
// {
// 	char	*cmd_path;
// 	int		i;
// 	char	*temp;

// 	i = 0;
// 	while (paths[i])
// 	{
// 		temp = ft_strjoin(paths[i], "/");
// 		if(!temp)
// 			return(NULL);
// 		cmd_path = ft_strjoin(temp, cmd);
// 		if(!cmd_path)
// 			return(NULL);
// 		free(temp);
// 		temp = NULL;
// 		if (access(cmd_path, F_OK) == 0)
// 			return (cmd_path);
// 		free(cmd_path);
// 		cmd_path = NULL;
// 		i++;
// 	}
// 	i = 0;
// 	while (paths[++i])
// 		free(paths[i]);
// 	free(paths);
// 	paths = NULL;
// 	return (NULL);
// }

// char	*get_cmd_path(char **paths, char *cmd)
// {
// 	int		i;
// 	char	*cmd_path;
// 	char	*temp;

// 	i = 0;
// 	cmd_path = NULL;
// 	temp = NULL;
// 	while (paths[i])
// 	{
// 		temp = ft_strjoin(paths[i], "/");
// 		if (!temp)
// 		{
// 			free(cmd_path);
// 			free_path_table(paths);
// 			return (NULL);
// 		}
// 		cmd_path = ft_strjoin(temp, cmd);
// 		free(temp);
// 		temp = NULL;
// 		if (!cmd_path)
// 		{
// 			free_path_table(paths);
// 			return (NULL);
// 		}
// 		if (!access(cmd_path, F_OK))
// 			break ;
// 		free(cmd_path);
// 		cmd_path = NULL;
// 		i++;
// 	}
// 	free_path_table(paths);
// 	return (cmd_path);
// }

char	*get_cmd_path(char **paths, char *cmd)
{
	char	*cmd_path;
	int		i;
	char	*temp;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(temp, cmd);
		if (!cmd_path)
			return (NULL);
		free(temp);
		temp = NULL;
		if (!access(cmd_path, F_OK))
			break ;
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	paths = NULL;
	return (cmd_path);
}

bool	execute_cmd(char **paths, char *cmd, char **envp)
{
	char	**tmp;
	char	*cmd_path;

	tmp = ft_split(cmd, ' ');
	cmd_path = get_cmd_path(paths, tmp[0]);
	if (!cmd_path)
	{
		error("Invalid command!\n");
		return (false);
	}
	return (execve(cmd_path, tmp, envp) >= 0);
}
