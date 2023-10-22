/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:34:43 by yothmani          #+#    #+#             */
/*   Updated: 2023/10/22 02:16:28 by yothmani         ###   ########.fr       */
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
	fd = open(file_path, permission, 0777);
	if (fd < 0)
		error("Bad file descriptor ! \n");
	if (dup2(fd, fd_1) == -1)
		error("input file descriptor failed \n");
	if (dup2(fd_p[fd_2], fd_2) == -1)
		error("output file descriptor failed \n");
	close(fd_p[fd_1]);
}

int	validation(int argc, char **argv)
{
	if (argc != 5)
		error("Usage: ./pipex <file1> <cmd1> <cmd2> <file2> !\n");
	if (access(argv[1], O_RDONLY) < 0)
		error("infile inaccessible !");
	return (0);
}

char	**extract_paths(char **envp)
{
	char	**paths_tab;
	char	*path;

	if (!envp)
		return (NULL);
	while (*envp && !ft_strnstr(*envp, "PATH=", 5))
		envp++;
	if (!*envp)
		return (NULL);
	path = ft_substr(*envp, 5, ft_strlen(*envp) - 5);
	paths_tab = ft_split(path, ':');
	free(path);
	// path = NULL;
	return (paths_tab);
}

char	*get_cmd_path(char **paths, char *cmd)
{
	char	*tmp;
	char	*cmd_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		tmp = NULL;
		if (access(cmd_path, F_OK) == 0)
		{
			clean_table(paths);
			paths = NULL;
			return (cmd_path);
		}
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}
	// clean_table(paths);
	// paths = NULL;
	return (NULL);
}

void	clean_table(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;	
	}
	free(tab);
	// tab = NULL;
}

bool	execute_cmd(char **paths, char *cmd, char **envp)
{
	char	**tmp;
	char	*cmd_path;
	char 	*error_msg;

	tmp = ft_split(cmd, ' ');
	cmd_path = get_cmd_path(paths, tmp[0]);
	if (!cmd_path)
	{
		clean_table(tmp);
		tmp = NULL;
		error_msg = ft_strjoin("command not found: ", cmd );
		error(error_msg);
		free(error_msg);
		
	}
	if(execve(cmd_path, tmp, envp)  == -1)
	{
		free(cmd_path);
		clean_table(tmp);
		error("execution failed!");
	}
	free(cmd_path);
    clean_table(tmp);
	return(false);
}
